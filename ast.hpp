#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

class Node
{
public:
    Node() {}
    virtual ~Node() {}
    virtual void print();
};

class Type : public Node
{
public:
    std::string name;

    Type() {}
    void print()
    {
        cout << name;
    }
};

class Expr : public Node
{
public:
    virtual void print()
    {
    }
};

class Block : public Expr
{
public:
    list<Expr> exprs;
    void print()
    {
    }
};

class Formal : public Node
{
public:
    std::string name;
    Type type;

    Formal() {}
    void print()
    {
    }
};

class Field : public Node
{
public:
    std::string name;
    std::string type;
    Expr initExpr;

    Field()
    {
    }
    void print()
    {
    }
};

class Method : public Node
{
public:
    std::string name;
    list<Formal> formals;
    Block block;
    std::string returnType;

    void print()
    {
    }
};

class Class : public Node
{
public:
    std::string class_name = "Object";
    std::string parent_class = NULL;
    list<Field> fields;
    list<Method> Methods;

    Class()
    {
    }
    void print()
    {
    }
};

class If : public Expr
{
public:
    Expr condExpr;
    Expr thenExpr;
    Expr elseExpr;

    If(Expr condExp, Expr thenExp)
    {
        condExpr = condExp;
        thenExpr = thenExp;
    }
    If(Expr condExp, Expr thenExp, Expr elseExp)
    {
        condExpr = condExp;
        thenExpr = thenExp;
        elseExpr = elseExp;
    }
    void print()
    {
    }
};

class While : public Expr
{
public:
    Expr condExpr;
    Expr bodyExpr;

    While(Expr condExp, Expr bodyExp)
    {
        condExpr = condExp;
        bodyExpr = bodyExp;
    }
    void print()
    {
    }
};

class Let : public Expr
{
public:
    std::string name;
    Type type;
    Expr expr;

    Let() {}
    void print()
    {
    }
};

class New : public Expr
{
};

class Program : public Node
{
};

class Assign : public Node
{
public:
    std::string name;
    Expr expr;
    Assign() {}
    void print()
    {
    }
};

class BinOp : public Node
{
public:
    std::string op;
    Expr expr1;
    Expr expr2;

    BinOp(Expr exp1, std::string o, Expr exp2)
    {
        op = o;
        expr1 = exp1;
        expr2 = exp2;
    }

    void print()
    {
    }
};
