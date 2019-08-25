#include "statement.hpp"
#include <iostream>

std::string NBlock::code_gen()
{
    std::string builder = "";
    for (auto statement : statements)
        builder += statement->code_gen() + ";\n";
    return builder;
}

std::string NStatement::code_gen()
{
    return "UNEXPECTED STATEMENT";
}

std::string NExpressionStatement::code_gen()
{
    return expression.code_gen();
}

std::string NVariableDeclaration::code_gen()
{
    std::string builder = "";
    builder += type.code_gen() + " " + id.code_gen();
    if (expression != NULL)
        builder += "=" + expression->code_gen();
    return builder;
}

std::string NFunctionDeclaration::code_gen()
{
    std::string builder = "";
    builder += type.code_gen() + " " + id.code_gen() + "(";
    for (int i = 0; i < args.size(); i++) {
        builder += args[i]->code_gen();
        // put a comma after unless it's the last item
        if (i != args.size() - 1) builder += ",";
    }
    builder += ") {" + block.code_gen() + "\n}";
    return builder;
}