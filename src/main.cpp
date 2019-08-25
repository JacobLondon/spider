#include <iostream>
#include "node/__init__.hpp"
#include "parser.hpp"
extern NBlock* root_block;
extern int yyparse();

int main(int argc, char** argv)
{
    yyparse();
    std::cout << root_block << std::endl;
    return 0;
}