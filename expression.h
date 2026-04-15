#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <iosfwd>

#include "int128.h"

class Expression;
class Const;
class Variable;
class Negate;
class Add;
class Subtract;
class Multiply;
class Divide;

class Expression {
public:
    using Variables = std::map<std::string, Int128>;

    virtual ~Expression() = default;

    virtual Int128 eval(const Variables& variables) const = 0;
    virtual Expression* clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
};

std::ostream& operator<<(std::ostream& out, const Expression& expression);

class Const : public Expression {
public:
    Const(const Int128& value);
    Const(int64_t value);

    Int128 eval(const Variables&) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;

private:
    Int128 value_;
};

class Variable : public Expression {
public:
    Variable(std::string name);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;

private:
    std::string name_;
};

class UnaryExpression : public Expression {
public:
    explicit UnaryExpression(const Expression& expression);
    UnaryExpression(const UnaryExpression& other);
    UnaryExpression& operator=(const UnaryExpression& other);

protected:
    std::unique_ptr<Expression> expression_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(const Expression& left, const Expression& right);
    BinaryExpression(const BinaryExpression& other);
    BinaryExpression& operator=(const BinaryExpression& other);

protected:
    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};

class Negate : public UnaryExpression {
public:
    explicit Negate(const Expression& expression);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;
};

class Add : public BinaryExpression {
public:
    Add(const Expression& left, const Expression& right);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;
};

class Subtract : public BinaryExpression {
public:
    Subtract(const Expression& left, const Expression& right);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;
};

class Multiply : public BinaryExpression {
public:
    Multiply(const Expression& left, const Expression& right);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;
};

class Divide : public BinaryExpression {
public:
    Divide(const Expression& left, const Expression& right);

    Int128 eval(const Variables& variables) const override;
    Expression* clone() const override;
    void print(std::ostream& out) const override;
};

Negate operator-(const Expression& expression);
Add operator+(const Expression& left, const Expression& right);
Subtract operator-(const Expression& left, const Expression& right);
Multiply operator*(const Expression& left, const Expression& right);
Divide operator/(const Expression& left, const Expression& right);
