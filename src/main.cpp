#include <iostream>
#include "grammar/parser.hpp"
extern NBlock* root_block;
extern int yyparse();

int main(int argc, char** argv)
{
    yyparse();
    std::cout << root_block->code_gen() << std::endl;
    return 0;
}