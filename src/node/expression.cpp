#include "expression.hpp"
#include "../grammar/parser.hpp"    // operators

std::string NExpression::code_gen()
{
    return "UNEXPECTED EXPRESSION";
}

std::string NInteger::code_gen()
{
    return std::to_string(value);
}

std::string NDouble::code_gen()
{
    return std::to_string(value);
}

std::string NBinaryOperator::code_gen()
{
    std::string oper;
    // op from Bison: 'comparison'
    switch (op) {
    case TCEQ:
        oper = "=="; break;
    case TCNE:
        oper = "!="; break;
    case TCLT:
        oper = "<"; break;
    case TCLE:
        oper = "<="; break;
    case TCGT:
        oper = ">"; break;
    case TCGE:
        oper = ">="; break;
    case TPLUS:
        oper = "+"; break;
    case TMINUS:
        oper = "-"; break;
    case TMUL:
        oper = "*"; break;
    case TDIV:
        oper = "/"; break;
    }

    return lhs.code_gen() + oper + rhs.code_gen();
}

std::string NIdentifier::code_gen()
{
    return name;
}

std::string NAssignment::code_gen()
{
    return id.code_gen() + "=" + value.code_gen();
}

std::string NMethodCall::code_gen()
{
    std::string builder = "";
    builder += id.code_gen() + "(";
    for (int i = 0; i < args.size(); i++) {
        builder += args[i]->code_gen();
        // put a comma after unless it's the last item
        if (i != args.size() - 1) builder += ",";
    }
    builder += ")";
    return builder;
}