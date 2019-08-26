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
    virtual std::string code_gen();
};

/**
 * Statements
 */

class NStatement : public Node {
public:
    virtual std::string code_gen();
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) : expression(expression) {}
    virtual std::string code_gen();
};

class NVariableDeclaration : public NStatement {
public:
    NIdentifier& type;
    NIdentifier& id;
    NExpression* expression;
    NVariableDeclaration(NIdentifier& type, NIdentifier& id) : type(type), id(id), expression(NULL) {}
    NVariableDeclaration(NIdentifier& type, NIdentifier& id, NExpression* expression) : type(type), id(id), expression(expression) {}
    virtual std::string code_gen();
};

class NFunctionDeclaration : public NStatement {
public:
    NIdentifier& type;
    NIdentifier& id;
    Variables args;
    NBlock& block;
    NFunctionDeclaration(NIdentifier& type, NIdentifier& id, Variables& args, NBlock& block) :
        type(type), id(id), args(args), block(block) {}
    virtual std::string code_gen();
};

class NIfDeclaration : public NStatement {
public:
    NExpression* expression;
    NBlock& block;
    NIfDeclaration(NExpression* expression, NBlock& block) : expression(expression), block(block) {}
    virtual std::string code_gen();
};
