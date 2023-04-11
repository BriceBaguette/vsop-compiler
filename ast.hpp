#include <iostream>
#include <string>
#include <map>
#include <list>
#include <iterator>

using namespace std;

class Node
{
public:
    Node() {}
};

class Type : public Node
{
public:
    string name;

    Type(string n) : name(n) {}

    void print()
    {
        cout << name;
    }
};

class Expr : public Node
{
public:
    Expr() {}

    virtual void print()
    {
    }
};

class Block : public Expr
{
public:
    list<Expr *> exprs;

    Block(list<Expr *> ex) : exprs(ex) {}

    void print()
    {
        bool first = true;
        cout << "[";
        for (list<Expr *>::iterator i = exprs.begin(); i != exprs.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print();
            }
            else
            {
                cout << ", ";
                (*i)->print();
            }
        }
        cout << "]";
    }
};

class Formal : public Node
{
public:
    string name;
    Type *type;

    Formal(string n, Type *t) : name(n), type(t) {}

    void print()
    {
        cout << name << ":";
        type->print();
    }
};

class Field : public Node
{
public:
    string name;
    Type *type;
    Expr *initExpr;

    Field(string n, Type *t) : name(n), type(t)
    {
        initExpr = NULL;
    }
    Field(string n, Type *t, Expr *initE) : name(n), type(t), initExpr(initE)
    {
    }

    void print()
    {
        if (initExpr == NULL)
        {
            cout << "Field(" << name << ", ";
            type->print();
            cout << ")";
        }
        else
        {
            cout << "Field(" << name << ", ";
            type->print();
            cout << ", ";
            initExpr->print();
            cout << ")";
        }
    }
};

class Method : public Node
{
public:
    string name;
    list<Formal *> formals;
    Type* returnType;
    Block *block;
    

    Method(string n, list<Formal *> f, Type* ret, Block *b) : name(n), formals(f),  returnType(ret), block(b) {}

    void print()
    {
        bool first = true;
        cout << "Method(" << name << ", [";
        formals.reverse();
        for (list<Formal *>::iterator i = formals.begin(); i != formals.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print();
            }
            else
            {
                cout << ", ";
                (*i)->print();
            }
        }
        cout << "], ";
        returnType->print();
        cout << ", ";
        block->print();
        cout << ")";
    }
};

class Class : public Node
{
public:
    string class_name;
    string parent_class;
    list<Field *> fields;
    list<Method *> Methods;

    Class(string class_n, list<Field *> f, list<Method *> M) : class_name(class_n), fields(f), Methods(M)
    {
        parent_class = "";
    }
    Class(string class_n, string parent_c, list<Field *> f, list<Method *> M) : class_name(class_n), parent_class(parent_c), fields(f), Methods(M) {}

    void print()
    {
        bool first = true;
        cout << "Class(" << class_name << ", ";
        if (parent_class == "")
            cout << "Object, [";
        else
            cout << parent_class << ", [";
        fields.reverse();
        for (list<Field *>::iterator i = fields.begin(); i != fields.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print();
            }
            else
            {
                cout << ", ";
                (*i)->print();
            }
        }
        first = true;
        cout << "], [";
        Methods.reverse();
        for (list<Method *>::iterator i = Methods.begin(); i != Methods.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print();
            }
            else
            {
                cout << ", ";
                (*i)->print();
            }
        }
        cout << "] )";
    }
};

class If : public Expr
{
public:
    Expr *condExpr;
    Expr *thenExpr;
    Expr *elseExpr;

    If(Expr *condExp, Expr *thenExp)
    {
        condExpr = condExp;
        thenExpr = thenExp;
    }
    If(Expr *condExp, Expr *thenExp, Expr *elseExp)
    {
        condExpr = condExp;
        thenExpr = thenExp;
        elseExpr = elseExp;
    }
    void print()
    {
        if (elseExpr == NULL)
        {
            cout << "If(";
            condExpr->print();
            cout << ",";
            thenExpr->print();
            cout << ")";
        }
        else
        {
            cout << "If(";
            condExpr->print();
            cout << ",";
            thenExpr->print();
            cout << ",";
            elseExpr->print();
            cout << ")";
        }
    }
};

class While : public Expr
{
public:
    Expr *condExpr;
    Expr *bodyExpr;

    While(Expr *condExp, Expr *bodyExp)
    {
        condExpr = condExp;
        bodyExpr = bodyExp;
    }
    void print()
    {
        cout << "While(";
        condExpr->print();
        cout << ",";
        bodyExpr->print();
        cout << ")";
    }
};

class Let : public Expr
{
public:
    string name;
    Type *type;
    Expr *initExpr;
    Expr *scopeExpr;

    Let(string n, Type *t, Expr *scopeE) : name(n), type(t), scopeExpr(scopeE)
    {
        initExpr = NULL;
    }
    Let(string n, Type *t, Expr *initE, Expr *scopeE) : name(n), type(t), initExpr(initE), scopeExpr(scopeE)
    {
    }

    void print()
    {
        if (initExpr == NULL)
        {
            cout << "Let(" << name << ",";
            type->print();
            cout << ",";
            scopeExpr->print();
            cout << ")";
        }
        else
        {
            cout << "Let(" << name << ",";
            type->print();
            cout << ",";
            initExpr->print();
            cout << ",";
            scopeExpr->print();
            cout << ")";
        }
    }
};

class New : public Expr
{
public:
    Type *type;

    New(Type *t) : type(t)
    {
    }

    void print()
    {
        cout << "New(";
        type->print();
        cout << ")";
    }
};

class Program : public Node
{
public:
    list<Class *> classes;

    Program(list<Class *> cls)
    {
        classes = cls;
    }

    void print()
    {
        bool first = true;
        cout << "[";
        classes.reverse();
        for (list<Class *>::iterator i = classes.begin(); i != classes.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print();
            }
            else
            {
                cout << ", "<< endl;
                (*i)->print();
            }
        }
        cout << "]" << endl;
    }
};

class Assign : public Expr
{
public:
    string name;
    Expr *expr;

    Assign(string n, Expr *ex)
    {
        name = n;
        expr = ex;
    }

    void print()
    {
        cout << "Assign(" << name << ",";
        expr->print();
        cout << ")";
    }
};

class BinOp : public Expr
{
public:
    string op;
    Expr *expr1;
    Expr *expr2;

    BinOp(Expr *exp1, string o, Expr *exp2)
    {
        op = o;
        expr1 = exp1;
        expr2 = exp2;
    }

    void print()
    {
        cout << "BinOp(" << op << ",";
        expr1->print();
        cout << ",";
        expr2->print();
        cout << ")";
    }
};

class UnOp : public Expr
{
public:
    string op;
    Expr *expr;

    UnOp(string o, Expr *exp)
    {
        op = o;
        expr = exp;
    }

    void print()
    {
        cout << "UnOp(" << op << ",";
        expr->print();
        cout << ")";
    }
};

class Call : public Expr
{
public:
    string name;
    Expr *objExpr;
    list<Expr *> args;

    Call(string n, list<Expr *> arg)
    {
        name = n;
        objExpr = NULL;
        args = arg;
    }
    Call(string n, Expr *objE, list<Expr *> arg)
    {
        name = n;
        objExpr = objE;
        args = arg;
    }

    void print()
    {
        bool first = true;
        if (objExpr != NULL)
        {
            cout << "Call(";
            objExpr->print();
            cout << "," << name << "[";
            for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
            {
                if (first)
                {
                    first = false;
                    (*i)->print();
                }
                else
                {
                    cout << ",";
                    (*i)->print();
                }
            }
            cout << "]"
                 << ")";
        }
        else
        {
            cout << "Call(self," << name << "[";
            for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
            {
                if (first)
                {
                    first = false;
                    (*i)->print();
                }
                else
                {
                    cout << ",";
                    (*i)->print();
                }
            }
            cout << "]"
                 << ")";
        }
    }
};

class Number : public Expr
{
public:
    string num;

    Number(int n)
    {
        num = to_string(n);
    }

    void print()
    {
        cout << num;
    }
};

class String : public Expr
{
public:
    string str;

    String(string s)
    {
        str = s;
    }

    void print()
    {
        cout << str;
    }
};

class Bool : public Expr
{
public:
    string bo;

    Bool(string b)
    {
        bo = b;
    }

    void print()
    {
        cout << bo;
    }
};

class Self : public Expr
{
public:
    Self() {}

    void print()
    {
        cout << "self";
    }
};