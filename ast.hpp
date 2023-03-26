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

    Type(std::string n) {
        name = n;
    }
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

    Block(list<Expr> ex){
        exprs = ex;
    }

    void print()
    {

        exprs.print();
    }
};

class Formal : public Node
{
public:
    std::string name;
    Type type;

    Formal(std::string n, Type t) {
        type = t;
        name = n;
    }

    void print()
    {
        cout << name << ":" << type << endl;
    }
};

class Field : public Node
{
public:
    std::string name;
    std::string type;
    Expr initExpr;

    Field(std::string n, std::string t)
    {
        name = n;
        type = t;
        initExpr = NULL
    }
    Field(std::string n, std::string t, Expr initE)
    {
        name = n;
        type = t;
        initExpr = initE
    }
    void print()
    {
        if (!initExpr)
            cout << "Field(" << name << "," << type << ")" << endl;
        else cout << "Field(" << name << "," << type << "," << initExpr << ")" << endl;
    }
};

class Method : public Node
{
public:
    std::string name;
    list<Formal> formals;
    Block block;
    std::string returnType;

    Method(std::string n, list<Formal> f, Block b, std::string ret){
        name = n;
        formals = f;
        block = b;
        returnType = ret;
    }

    void print()
    {
        cout << "Method(" << name << "[";
        formals.print();
        cout << "]" << returnType;
        block.print();
        cout << ")" << endl;
    }
};

class Class : public Node
{
public:
    std::string class_name;
    std::string parent_class;
    list<Field> fields;
    list<Method> Methods;

    Class(std::string class_n, list<Field> f, list<Method> M)
    {
        class_name = class_n;
        parent_class = NULL;
        fields = f;
        Methods = M;
    }
    Class(std::string class_n, std::string parent_c, list<Field> f, list<Method> M)
    {
        class_name = class_n;
        parent_class = parent_c;
        fields = f;
        Methods = M;
    }

    void print()
    {
        cout << "Class(" << class_name;
        if (!parent_class)
            cout << "Object";
        else cout << parent_class << "[";
        fields.print();
        cout << "]" << "[";
        Methods.print();
        cout << "] )" << endl;
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
        if(!elseExpr){
            cout << "If(";
            condExpr.print();
            cout << ",";
            thenExpr.print();
            cout << ")" << endl;
        }else {
            cout << "If(";
            condExpr.print();
            cout << ",";
            thenExpr.print();
            cout << ",";
            elseExpr.print();
            cout << ")" << endl;
        }
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
        cout << "While(";
        condExpr.print();
        cout << ",";
        bodyExpr.print();
        cout << ")" << endl;
    }
};

class Let : public Expr
{
public:
    std::string name;
    Type type;
    Expr initExpr;
    Expr scopeExpr;

    Let(std::string n, Type t, Expr scopeE) {
        name = n;
        type = t;
        initExpr = NULL;
        scopeExpr = scopeE;
    }
    Let(std::string n, Type t, Expr initE, Expr scopeE) {
        name = n;
        type = t;
        initExpr = initE;
        scopeExpr = scopeE;
    }

    void print()
    {
        if(!initExpr){
            cout << "Let(" << name << "," << type ",";
            scopeExpr.print();
            cout << ")" << endl;
        }else {
            cout << "Let(" << name << "," << type ",";
            initExpr.print();
            cout << ",";
            scopeExpr.print();
            cout << ")" << endl;
        }
    }
};

class New : public Expr
{
public:
    Type type;

    New(Type t){
        type = t;
    }

    void print()
    {
        cout << "New(" << type << ")" << endl;
    }
};

class Program : public Node
{
public:
    list<Class> classes;

    Program(list<Class> cls){
        classes = cls;
    }

    void print()
    {
        cout << "[";
        classes.print();//rajouter , entre les classes
        cout << "]";
    }
};

class Assign : public Node
{
public:
    std::string name;
    Expr expr;

    Assign(std::string n, Expr ex) {
        name = n;
        expr = ex;
    }

    void print()
    {
        cout << "Assign(" << name "," << expr << ")" << endl;
    }
};

class BinOp : public Expr
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
        cout << "BinOp(" << op << "," ;
        expr1.print();
        cout << ",";
        expr2.print();
        cout << ")" << endl;
    }
};

class UnOp : public Expr
{
public:
    std::string op;
    Expr expr;

    UnOp(std::string o, Expr exp)
    {
        op = o;
        expr = exp;
    }

    void print()
    {
        cout << "UnOp(" << op << ",";
        expr.print();
        cout << ")" << endl;
    }
};

class Call : public Expr
{
public:
    std::string name;
    Expr objExpr;
    list<Expr> args;

    Call(std::string n, list<Expr> arg)
    {
        name = n;
        objExpr = NULL;
        args = arg;
    }
    Call(std::string n, Expr objE, list<Expr> arg){}
    {
        name = n;
        objExpr = objE;
        args = arg;
    }

    void print()
    {
        if(objExpr!= NULL){
            cout << "Call(";
            objExpr.print();
            cout << "," << name << "[";
            args.print();
            cout << "]" << ")" << endl;
        }else{
            cout << "Call(self," << name << "[";
            args.print();
            cout << "]" << ")" << endl;
        }
    }
};

class Number : public Expr
{
public:
    std::string num;

    Number(float n){
        num = n;
    }

    void print(){
        cout << num << endl;
    }
}

class String : public Expr
{
public:
    std::string str;

    String(std::string s){
        str = s;
    }

    void print(){
        cout << str << endl;
    }
}

class Bool : public Expr
{
public:
    bool bo;

    Bool(bool b){
        bo = b;
    }

    void print(){
        cout << bo << endl;
    }
}