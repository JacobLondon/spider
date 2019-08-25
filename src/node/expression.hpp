#pragma once
#include <string>
#include <vector>
#include "node.hpp"

class NExpression;

using Expressions = std::vector<NExpression *>;

class NExpression : public Node {
};

/**
 * Basic types
 */

class NInteger : public NExpression {
public:
    long long value;
    NInteger(long long value) : value(value) {}
    std::string code_gen();
};

class NDouble : public NExpression {
public:
    double value;
    NDouble(double value) : value(value) {}
    std::string code_gen();
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
    std::string code_gen();
};

/**
 * Identifier based expressions
 */

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) {}
    std::string code_gen();
};

class NAssignment : public NExpression {
public:
    NIdentifier& id;
    NExpression& value;
    NAssignment(NIdentifier& id, NExpression value) : id(id), value(value) {}
    std::string code_gen();
};

class NMethodCall : public NExpression {
public:
    const NIdentifier& id;
    Expressions args;
    NMethodCall(const NIdentifier& id, Expressions& args) : id(id), args(args) {}
    NMethodCall(const NIdentifier& id) : id(id) {}
    std::string code_gen();
};
