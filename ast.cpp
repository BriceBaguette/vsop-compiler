#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;
#include "ast.hpp"

class Node
{
public:
    std::string name;
    list<Node> children;
}

class Class : public Node
{
public:
    list<Field> fields;
    list<Method> Methods;

    void print()
    {
    }
}

class Field : public Node
{

}

class Method : public Node
{
    list<Formal> formals;
    Block block;
}

class Block : public Expr
{
    list<Expr> exprs;
}

class Expr : public Node
{
}

class Formal : public Node
{

}

class If : public Expr
{

}

class While : public Expr
{

}

class Else : public Expr
{
}

class Let : public Expr
{
}

class New : public Expr
{
}

class Program : public Node
{
}

class Type : public Node
{
}

class Assign : public Node
{
}