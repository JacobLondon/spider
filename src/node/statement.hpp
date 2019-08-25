#pragma once
#include <vector>
#include "expression.hpp"

class NStatement;
class NVariableDeclaration;

using Statements = std::vector<NStatement *>;
using Variables = std::vector<NVariableDeclaration *>;

/**
 * Statement interface
 */

class NBlock : public NExpression {
public:
    Statements statements;
    NBlock() {}
    std::string code_gen();
};

/**
 * Statements
 */

class NStatement : public Node {
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) : expression(expression) {}
    std::string code_gen();
};

class NVariableDeclaration : public NStatement {
public:
    const NIdentifier& type;
    NIdentifier& id;
    NExpression* expression;
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id) : type(type), id(id) {}
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression* expression) : type(type), id(id), expression(expression) {}
    std::string code_gen();
};

class NFunctionDeclaration : public NStatement {
public:
    const NIdentifier& type;
    const NIdentifier& id;
    Variables args;
    NBlock& block;
    NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, const Variables& args, NBlock& block) :
        type(type), id(id), args(args), block(block) {}
    std::string code_gen();
};
