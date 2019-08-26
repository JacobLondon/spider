%{
    #include "../node/__init__.hpp"
    #include <cstdio>
    NBlock* root_block;
    extern int yylex();
    void yyerror(const char* s) { printf("Error: %s\n", s); }
%}

%code requires { #include "../node/__init__.hpp" }

%union {
    Node*                               node;
    NBlock*                             block;
    NExpression*                        expr;
    NStatement*                         stmt;
    NIdentifier*                        ident;
    NVariableDeclaration*               var_decl;
    std::vector<NVariableDeclaration*>* varvec;
    std::vector<NExpression*>*          exprvec;
    std::string*                        string;
    int                                 token;
}

/* terminal symbols */
%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token>  TCEQ TCNE TCLT TCLE TCGT TCGE TEQUAL
%token <token>  TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT TCOLON TRARROW
%token <token>  TDEF TIF TWHILE
%token <token>  TPLUS TMINUS TMUL TDIV

/* nonterminal symbols */
%type <ident>   ident
%type <expr>    numeric expr 
%type <varvec>  func_decl_args
%type <exprvec> call_args
%type <block>   program stmts block
%type <stmt>    stmt var_decl func_decl if_decl while_decl
%type <token>   comparison

/* operator precedence */
%left TCOMMA
%right TEQUAL
%left TCEQ TCNE
%left TCGT TCGE
%left TCLT TCLE
%left TPLUS TMINUS
%left TMUL TDIV
%left TDOT TCOLON
%left TLPAREN TRPAREN

%start program

%%

program:
      stmts                             { root_block = $1; }
    ;

stmts:
      stmt                              { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
    | stmts stmt                        { $1->statements.push_back($<stmt>2); }
    ;

stmt:
      var_decl
    | if_decl
    | while_decl
    | func_decl
    | expr                              { $$ = new NExpressionStatement(*$1); }
    ;

block:
      TLBRACE stmts TRBRACE             { $$ = $2; }
    | TLBRACE TRBRACE                   { $$ = new NBlock(); }
    ;

/* shift/reduce conflict - ident TCOLON ident*/
var_decl:
      ident[V] TCOLON ident[T] TEQUAL expr[E]
                                        { $$ = new NVariableDeclaration(*$T, *$V, $E); }
    | ident[V] TCOLON ident[T]          { $$ = new NVariableDeclaration(*$T, *$V); }
    ;

func_decl:
      TDEF ident[N] TLPAREN func_decl_args[A] TRPAREN TRARROW ident[T] block[B]
                                        { $$ = new NFunctionDeclaration(*$T, *$N, *$A, *$B); delete $A; }
    ;

func_decl_args:
      /* no args */                     { $$ = new Variables(); }
    | var_decl                          { $$ = new Variables(); $$->push_back($<var_decl>1); }
    | func_decl_args TCOMMA var_decl    { $1->push_back($<var_decl>3); }
    ;

if_decl:
      TIF expr[E] block[B]              { $$ = new NIfDeclaration($E, *$B); }
    ;

while_decl:
      TWHILE expr[E] block[B]           { $$ = new NWhileDeclaration($E, *$B); }
    ;

ident:
      TIDENTIFIER                       { $$ = new NIdentifier(*$1); delete $1; }
    ;

numeric:
      TINTEGER                          { $$ = new NInteger(atol($1->c_str())); delete $1; }
    | TDOUBLE                           { $$ = new NDouble(atof($1->c_str())); delete $1; }
    ;

/* shift/reduce conflict - ident */
expr:
      ident TEQUAL expr                 { $$ = new NAssignment(*$<ident>1, *$3); }
    | ident TLPAREN call_args TRPAREN   { $$ = new NMethodCall(*$1, *$3); delete $3; }
    | ident                             { $<ident>$ = $1; }
    | numeric
    | expr comparison expr              { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | TLPAREN expr TRPAREN              { $$ = $2; }
    ;

call_args:
      /* no args */                     { $$ = new Expressions(); }
    | expr                              { $$ = new Expressions(); $$->push_back($1); }
    | call_args TCOMMA expr             { $1->push_back($3); }
    ;

comparison:
      TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE 
    | TPLUS | TMINUS | TMUL | TDIV
    ;

%%