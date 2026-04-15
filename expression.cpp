#include "expression.h"

#include <iostream>
#include <utility>

std::ostream& operator<<(std::ostream& out, const Expression& expression) {
    expression.print(out);
    return out;
}

Const::Const(const Int128& value) : value_(value) {}

Const::Const(int64_t value) : value_(value) {}

Int128 Const::eval(const Variables&) const {
    return value_;
}

Expression* Const::clone() const {
    return new Const(*this);
}

void Const::print(std::ostream& out) const {
    out << value_;
}

Variable::Variable(std::string name) : name_(std::move(name)) {}

Int128 Variable::eval(const Variables& variables) const {
    auto it = variables.find(name_);
    if (it == variables.end()) {
        return Int128();
    }
    return it->second;
}

Expression* Variable::clone() const {
    return new Variable(*this);
}

void Variable::print(std::ostream& out) const {
    out << name_;
}

UnaryExpression::UnaryExpression(const Expression& expression) : expression_(expression.clone()) {}

UnaryExpression::UnaryExpression(const UnaryExpression& other) : expression_(other.expression_->clone()) {}

UnaryExpression& UnaryExpression::operator=(const UnaryExpression& other) {
    if (this != &other) {
        expression_.reset(other.expression_->clone());
    }
    return *this;
}

BinaryExpression::BinaryExpression(const Expression& left, const Expression& right)
    : left_(left.clone()), right_(right.clone()) {}

BinaryExpression::BinaryExpression(const BinaryExpression& other)
    : left_(other.left_->clone()), right_(other.right_->clone()) {}

BinaryExpression& BinaryExpression::operator=(const BinaryExpression& other) {
    if (this != &other) {
        left_.reset(other.left_->clone());
        right_.reset(other.right_->clone());
    }
    return *this;
}

Negate::Negate(const Expression& expression) : UnaryExpression(expression) {}

Int128 Negate::eval(const Variables& variables) const {
    return -expression_->eval(variables);
}

Expression* Negate::clone() const {
    return new Negate(*this);
}

void Negate::print(std::ostream& out) const {
    out << "(-";
    expression_->print(out);
    out << ")";
}

Add::Add(const Expression& left, const Expression& right) : BinaryExpression(left, right) {}

Int128 Add::eval(const Variables& variables) const {
    return left_->eval(variables) + right_->eval(variables);
}

Expression* Add::clone() const {
    return new Add(*this);
}

void Add::print(std::ostream& out) const {
    out << "(";
    left_->print(out);
    out << " + ";
    right_->print(out);
    out << ")";
}

Subtract::Subtract(const Expression& left, const Expression& right) : BinaryExpression(left, right) {}

Int128 Subtract::eval(const Variables& variables) const {
    return left_->eval(variables) - right_->eval(variables);
}

Expression* Subtract::clone() const {
    return new Subtract(*this);
}

void Subtract::print(std::ostream& out) const {
    out << "(";
    left_->print(out);
    out << " - ";
    right_->print(out);
    out << ")";
}

Multiply::Multiply(const Expression& left, const Expression& right) : BinaryExpression(left, right) {}

Int128 Multiply::eval(const Variables& variables) const {
    return left_->eval(variables) * right_->eval(variables);
}

Expression* Multiply::clone() const {
    return new Multiply(*this);
}

void Multiply::print(std::ostream& out) const {
    out << "(";
    left_->print(out);
    out << " * ";
    right_->print(out);
    out << ")";
}

Divide::Divide(const Expression& left, const Expression& right) : BinaryExpression(left, right) {}

Int128 Divide::eval(const Variables& variables) const {
    return left_->eval(variables) / right_->eval(variables);
}

Expression* Divide::clone() const {
    return new Divide(*this);
}

void Divide::print(std::ostream& out) const {
    out << "(";
    left_->print(out);
    out << " / ";
    right_->print(out);
    out << ")";
}

Negate operator-(const Expression& expression) {
    return Negate(expression);
}

Add operator+(const Expression& left, const Expression& right) {
    return Add(left, right);
}

Subtract operator-(const Expression& left, const Expression& right) {
    return Subtract(left, right);
}

Multiply operator*(const Expression& left, const Expression& right) {
    return Multiply(left, right);
}

Divide operator/(const Expression& left, const Expression& right) {
    return Divide(left, right);
}
