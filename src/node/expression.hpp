#pragma once
#include <string>
#include <vector>
#include "node.hpp"

class NExpression;

using Expressions = std::vector<NExpression *>;

class NExpression : public Node {
public:
    virtual std::string code_gen();
};

/**
 * Basic types
 */

class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) {}
    virtual std::string code_gen();
};

class NDouble : public NExpression {
public:
    double value;
    NDouble(double value) : value(value) {}
    virtual std::string code_gen();
};

/**
 * Operations
 */

class NBinaryOperator : public NExpression {
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) : lhs(lhs), op(op), rhs(rhs) {}
    virtual std::string code_gen();
};

/**
 * Identifier based expressions
 */

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) {}
    virtual std::string code_gen();
};

class NAssignment : public NExpression {
public:
    NIdentifier& id;
    NExpression& value;
    NAssignment(NIdentifier& id, NExpression value) : id(id), value(value) {}
    virtual std::string code_gen();
};

class NMethodCall : public NExpression {
public:
    NIdentifier& id;
    Expressions args;
    NMethodCall(NIdentifier& id, Expressions& args) : id(id), args(args) {}
    NMethodCall(NIdentifier& id) : id(id) {}
    virtual std::string code_gen();
};
