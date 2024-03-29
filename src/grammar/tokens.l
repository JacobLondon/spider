%{
#include <iostream>
#include <string>
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() {return 1;}
%}

%option yylineno

%%

[ \t\r\n]               ;
"def"                   return TOKEN(TDEF);
"if"                    return TOKEN(TIF);
"while"                 return TOKEN(TWHILE);
[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]*          SAVE_TOKEN; return TDOUBLE;
[0-9]+                  SAVE_TOKEN; return TINTEGER;
"->"                    return TOKEN(TRARROW);
"=="                    return TOKEN(TCEQ);
"!="                    return TOKEN(TCNE);
"<="                    return TOKEN(TCLE);
">="                    return TOKEN(TCGE);
">"                     return TOKEN(TCGT);
"<"                     return TOKEN(TCLT);
"="                     return TOKEN(TEQUAL);
"("                     return TOKEN(TLPAREN);
")"                     return TOKEN(TRPAREN);
"{"                     return TOKEN(TLBRACE);
"}"                     return TOKEN(TRBRACE);
"."                     return TOKEN(TDOT);
","                     return TOKEN(TCOMMA);
"+"                     return TOKEN(TPLUS);
"-"                     return TOKEN(TMINUS);
"*"                     return TOKEN(TMUL);
"/"                     return TOKEN(TDIV);
":"                     return TOKEN(TCOLON);
.                       std::cerr << "Line " << yylineno << ": unexpected token '" << yytext << "'" << std::endl; exit(-1);

%%