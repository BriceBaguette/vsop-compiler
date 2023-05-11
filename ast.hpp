#include <iostream>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <algorithm>

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

class Class;

class Expr : public Node
{
public:
    Expr() {}

    virtual void print()
    {
    }

    virtual string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return "unit";
    }

    virtual int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    virtual void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "()";
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
        exprs.reverse();
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

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if (exprs.empty())
            return "unit";
        else
        {
            return exprs.front()->get_type(id_map, classes, self);
        }
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        for (list<Expr *>::iterator i = exprs.begin(); i != exprs.end(); ++i)
        {
            error += (*i)->general_check(id_map, classes, self);
        }
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        bool first = true;
        cout << "[";
        exprs.reverse();
        for (list<Expr *>::iterator i = exprs.begin(); i != exprs.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, classes, self);

                cout << " : " << (*i)->get_type(id_map, classes, self);
            }
            else
            {
                cout << ", ";
                (*i)->print_semantic(id_map, classes, self);
                cout << " : " << (*i)->get_type(id_map, classes, self);
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
        cout << name << " : ";
        type->print();
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return type->name;
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_type_exists(id_map, classes, self);
        if (error == 0)
            id_map.insert(pair<string, string>(name, type->name)); /* SHOULD INSERT IN FORMALS TABLE */
        return error;
    }

    int check_type_exists(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    { 
        int error = 0;
        if (type->name != "int32" && type->name != "bool" && type->name != "string" && type->name != "unit")
        {
            if (classes.find(type->name) == classes.end())
            {
                cout << "Error in formal " << name << " : the type " << type->name << " does not exist" << endl;
                error = 1;
            }
        }
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << name << " : ";
        id_map.insert(pair<string, string>(name, type->name)); /* SHOULD INSERT IN FORMALS TABLE */
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

    int check_typing_errors(map<string, string> &id_map, map<string, Class*> classes, string self, map<string, string> &parents)
    {
        int error = 0;
        if (initExpr != NULL)
        {
            string it = initExpr->get_type(id_map, classes, self);
            if (type->name != it)
            {
                if(it != "int32" || it != "bool" || it != "string" || it != "unit")
                {
                    error += check_typing_errors_parent(id_map, classes, it, parents);
                }
                else
                {
                    error = 1;
                }
                if (error != 0)
                {
                    cout << "Error in field " << name << " : the type should be of " << type->name << " instead of " << initExpr->get_type(id_map, classes, self) << endl;
                }
            }
        }
        return error;
    }




    int check_typing_errors_parent(__attribute__((unused)) map<string, string> &id_map, __attribute__((unused)) map<string, Class*> classes, __attribute__((unused)) string type_name, __attribute__((unused)) map<string, string> &parents)
    {
        int error = 0;
        string parent = parents.find(type_name)->second;
        if (type->name == parent)
        {
            return error;
        }
        else if (parent == "Object")
        {
            error = 1;
            return error;
        }
        else
        {
            return error = check_typing_errors_parent(id_map, classes, parent, parents);
        }   
        return 1;
    }




    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return type->name;
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self, __attribute__ ((unused)) map<string, string> &parents)
    {
        int error = 0; 
        if (initExpr != NULL)
        {
            error += initExpr->general_check(id_map, classes, self);
        }
        error += check_typing_errors(id_map, classes, self, parents);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if (initExpr == NULL)
        {
            cout << "Field(" << name << ", ";
            id_map.insert(pair<string, string>(name, type->name)); /*INSERT INTO FIELD TABLE*/
            cout << type->name << ")";
        }
        else
        {
            cout << "Field(" << name << ", ";
            id_map.insert(pair<string, string>(name, type->name));
            cout << type->name << ", " << endl << "         ";
            initExpr->print_semantic(id_map, classes, self);
            cout << endl << "       : " << initExpr->get_type(id_map, classes, self) << ")";
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
    
    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return returnType->name;
    }

    int check_typing_errors(map<string, string> &id_map, map<string, Class*> classes, string self, map<string, string> &parents)
    {
        int error = 0;
        string bt = block->get_type(id_map, classes, self);
        if(returnType->name != "int32" && returnType->name != "bool" && returnType->name != "string" && returnType->name != "unit")
        {
            if (classes.find(returnType->name) == classes.end())
            {
                cout << "Error in method " << name << " : the return type " << returnType->name << " does not exist" << endl;
                return 1;
            }
        }
        if(returnType->name != bt)
        {
            if(bt != "int32" || bt != "bool" || bt != "string" || bt != "unit")
            {
                error += check_typing_errors_parent(id_map, classes, bt, parents);
            }
            else
            {
                error += 1;
            }
            if (error != 0)
            {
                cout << "Error in method " << name << " : the block type should be of " << returnType->name << " instead of " << block->get_type(id_map, classes, self) << endl;
            }
        }
        return error;
    }

    int check_typing_errors_parent(__attribute__((unused)) map<string, string> &id_map, __attribute__((unused)) map<string, Class*> classes, __attribute__((unused)) string type_name, __attribute__((unused)) map<string, string> &parents)
    {
        int error = 0;
        string parent = parents.find(type_name)->second;
        if (returnType->name == parent)
        {
            return error;
        }
        else if (parent == "Object")
        {
            error = 1;
            return error;
        }
        else
        {
            return error = check_typing_errors_parent(id_map, classes, parent, parents);
        }   
        return 1;
    }
    
    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self, __attribute__ ((unused)) map<string, string> &parents)
    {
        int error = 0;
        formals.reverse();
        for (list<Formal *>::iterator i = formals.begin(); i != formals.end(); ++i)
        {
            id_map.insert(pair<string, string>((*i)->name, (*i)->type->name));/*INSERT INTO FORMAL TABLE*/
            error += (*i)->general_check(id_map, classes, self);
        }
        error += check_typing_errors(id_map, classes, self, parents);
        error += block->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        bool first = true;
        cout << "Method(" << name << ", [";
        for (list<Formal *>::iterator i = formals.begin(); i != formals.end(); ++i)
        {
            id_map.insert(pair<string, string>((*i)->name, (*i)->type->name)); /*INSERT INTO FORMAL TABLE*/
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, classes, self);
            }
            else
            {
                cout << ", ";
                (*i)->print_semantic(id_map, classes, self);
            }
        }
        cout << "], " << returnType->name << ", " << endl << "       ";
        block->print_semantic(id_map, classes, self);
        cout << endl << "       : " << block->get_type(id_map, classes, self) << ")";
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
        parent_class = "Object";
    }
    Class(string class_n, string parent_c, list<Field *> f, list<Method *> M) : class_name(class_n), parent_class(parent_c), fields(f), Methods(M) {}

    void print()
    {
        bool first = true;
        cout << "Class(" << class_name << ", " << parent_class << ", " << endl << "    " << "[";
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
        cout << "], " << endl << "    [";
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
                cout << endl;
            }
        }
        cout << "] )";
    }


    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self, __attribute__ ((unused)) map<string, string> &parents)
    {

        int error = 0;
        fields.reverse();
        for (list<Field *>::iterator i = fields.begin(); i != fields.end(); ++i)
        {
            id_map.insert(pair<string, string>((*i)->name, (*i)->type->name)); /*INSERT INTO FIELD TABLE*/
            error += (*i)->general_check(id_map, classes, self, parents);
        }
        Methods.reverse();
        for (list<Method *>::iterator i = Methods.begin(); i != Methods.end(); ++i)
        {
            error += (*i)->general_check(id_map, classes, self, parents);
        }
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        bool first = true;
        cout << "Class(" << class_name << ", " << parent_class << ", " << endl << "    [";
        for (list<Field *>::iterator i = fields.begin(); i != fields.end(); ++i)
        {
            id_map.insert(pair<string, string>((*i)->name, (*i)->type->name)); /*INSERT INTO FIELD TABLE*/
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, classes, self);
            }
            else
            {
                cout << ", " << endl << "     ";
                (*i)->print_semantic(id_map, classes, self);
            }
        }
        first = true;
        cout << "], " << endl << "    [";
        for (list<Method *>::iterator i = Methods.begin(); i != Methods.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, classes, self);
            }
            else
            {
                cout << ", " << endl << "     ";
                (*i)->print_semantic(id_map, classes, self);
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
        elseExpr = NULL;
    }
    If(Expr *condExp, Expr *thenExp, Expr *elseExp)
    {
        condExpr = condExp;
        thenExpr = thenExp;
        elseExpr = elseExp;
    }

    int check_typing_errors(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if (condExpr->get_type(id_map, classes, self) != "bool")
        {
            cout << "Error in If : the condition should be of type Bool instead of " << condExpr->get_type(id_map, classes, self) << endl;
            return error = 1;
        }
        if (thenExpr->get_type(id_map, classes, self) == "int32" || thenExpr->get_type(id_map, classes, self) == "bool" || thenExpr->get_type(id_map, classes, self) == "string")
        {
            if (elseExpr != NULL)
            {
                if (elseExpr->get_type(id_map, classes, self) != thenExpr->get_type(id_map, classes, self) && elseExpr->get_type(id_map, classes, self) != "unit")
                {
                    cout << "Error in If : the then and else expressions should be of the same type (Currently " << thenExpr->get_type(id_map, classes, self) << " and " << elseExpr->get_type(id_map, classes, self) << ")" << endl;
                    error = 1;
                }
            }
        }
        return error;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if (elseExpr == NULL || thenExpr->get_type(id_map, classes, self) == "unit" || elseExpr->get_type(id_map, classes, self) == "unit")
            return "unit";
        else if (thenExpr->get_type(id_map, classes, self) != "int32" && thenExpr->get_type(id_map, classes, self) != "bool" && thenExpr->get_type(id_map, classes, self) != "string")
        {
            return find_ancestor_type(thenExpr->get_type(id_map, classes, self), elseExpr->get_type(id_map, classes, self), classes);
        }
        else
        {
            return elseExpr->get_type(id_map, classes, self);        
        }
    }

    string find_ancestor_type(string type1, string type2,  map<string, Class*> classes)
    {
        if (type1 == type2)
        {
            return type1;
        } 
        else 
        {
            string parent = classes.find(type1)->second->parent_class;
            while (parent != "Object")
            {
                if (parent == type2)
                {
                    return parent;
                } 
                else
                {
                    parent = classes.find(parent)->second->parent_class;
                }
            }
            if (parent == type2)
            {
                return parent;
            }
            else
            {
                return find_ancestor_type(type1, classes.find(type2)->second->parent_class, classes);
            }
        }
    }

    void print()
    {
        if (elseExpr == NULL)
        {
            cout << "If(";
            condExpr->print();
            cout << ", ";
            thenExpr->print();
            cout << ")";
        }
        else
        {
            cout << "If(";
            condExpr->print();
            cout << ", ";
            thenExpr->print();
            cout << ", ";
            elseExpr->print();
            cout << ")";
        }
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_typing_errors(id_map, classes, self);
        error += condExpr->general_check(id_map, classes, self);
        error += thenExpr->general_check(id_map, classes, self);
        if (elseExpr != NULL)
            error += elseExpr->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if (elseExpr == NULL)
        {
            cout << "If(";
            condExpr->print_semantic(id_map, classes, self);
            cout << " : " << condExpr->get_type(id_map, classes, self) << ", ";
            thenExpr->print_semantic(id_map, classes, self);
            cout << " : " << thenExpr->get_type(id_map, classes, self) << ")";
        }
        else
        {
            cout << "If(";
            condExpr->print_semantic(id_map, classes, self);
            cout << " : " << condExpr->get_type(id_map, classes, self) << ", ";
            thenExpr->print_semantic(id_map, classes, self);
            cout << " : " << thenExpr->get_type(id_map, classes, self) << ", ";
            elseExpr->print_semantic(id_map, classes, self);
            cout << " : " << elseExpr->get_type(id_map, classes, self) << ")";
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
        cout << ", ";
        bodyExpr->print();
        cout << ")";
    }

    int check_typing_errors(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if(condExpr->get_type(id_map, classes, self) != "bool")
        {
            cout << "Error in while : the condition should be of type bool instead of " << condExpr->get_type(id_map, classes, self) << endl;
            error = 1;
        }
        return error;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return "unit";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_typing_errors(id_map, classes, self);
        error += condExpr->general_check(id_map, classes, self);
        error += bodyExpr->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "While(";
        condExpr->print_semantic(id_map, classes, self);
        cout << " : " << condExpr->get_type(id_map, classes, self) << ", ";
        bodyExpr->print_semantic(id_map, classes, self);
        cout << " : " << bodyExpr->get_type(id_map, classes, self) << ")";
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
        cout << "Let(" << name << ", ";
        type->print();
        cout << ", ";
        if (initExpr != NULL)
        {
            initExpr->print();
            cout << ", ";
        }
        scopeExpr->print();
        cout << ")";
    }

    int check_let_id_type(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if(type->name != "int32" && type->name != "bool" && type->name != "string" && type->name != "unit")
        {
            if (classes.find(type->name) == classes.end())
            {
                cout << "Error in Let " << name << " : the return type " << type->name << " does not exist" << endl;
                return 1;
            }
        }
        if (initExpr != NULL)
        {
            if (initExpr->get_type(id_map, classes, self) != type->name)
            {
                cout << "Error in let " << name << " : the type of the expression should be " << type->name << " instead of " << initExpr->get_type(id_map, classes, self) << endl;
                error = 1;
            }
            
        }
        id_map.insert({name, type->name});
        return error;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        id_map.insert({name, type->name});
        return scopeExpr->get_type(id_map, classes, self);
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_let_id_type(id_map, classes, self);
        if (initExpr != NULL)
            error += initExpr->general_check(id_map, classes, self);
        error += scopeExpr->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "Let(" << name << ", " << type->name << ", ";
        id_map.insert({name, type->name});
        
        if (initExpr != NULL)
        {
            initExpr->print_semantic(id_map, classes, self);
            cout << " : " << initExpr->get_type(id_map, classes, self) << ", ";
        }
        scopeExpr->print_semantic(id_map, classes, self);
        cout << " : " << get_type(id_map, classes, self) << ")";
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

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "New(" << type->name << ")";
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return type->name;
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }
};

class Program : public Node
{
public:
    list<Class *> classes;
    map<string, string> &id_map;
    map<string, Class*> class_map;
    map<string, string> &classAndParent;

    Program(list<Class *> cls): id_map(*(new map<string, string>)), classAndParent(*(new map<string, string>))
    {
        classes = cls;
        init();
    }

    void init(){
        //INIT OF CLASS OBJECT
        list<Field *> fields;
        list<Method *> methods;
        list<Expr *> exprs;
        list<Formal *> formals, formals1, formals2, formals3;
        formals1.push_back(new Formal("s",new Type("string")));
        Method* m1 =new Method("print", formals1, new Type("Object"), new Block(exprs));
        methods.push_back(m1);
        formals2.push_back(new Formal("b", new Type("bool")));
        Method* m2 =new Method("printBool", formals2, new Type("Object"), new Block(exprs));
        methods.push_back(m2);
        formals3.push_back(new Formal("i", new Type("int32")));
        Method* m3 =new Method("printInt32", formals3, new Type("Object"), new Block(exprs));
        methods.push_back(m3);
        Method* m4 =new Method("inputLine", formals, new Type("string"), new Block(exprs));
        methods.push_back(m4);
        Method* m5 =new Method("inputBool", formals, new Type("bool"), new Block(exprs));
        methods.push_back(m5);
        Method* m6 =new Method("inputInt32", formals, new Type("int32"), new Block(exprs));
        methods.push_back(m6);
        class_map.insert({"Object", new Class("Object", fields, methods)});

    }

    int checkClassExistence()
    {
        //map<string, string> classAndParent;
        int error = 0;
        list<string> names;
        int main_check = 0;
        classes.reverse();
        for (list<Class *>::iterator i = classes.begin(); i != classes.end(); ++i)
        {
            names.push_back((*i)->class_name);
            class_map.insert({(*i)->class_name, *i});
            if ((*i)->class_name == "Main")
            {
                for (list<Method *>::iterator j = (*i)->Methods.begin(); j != (*i)->Methods.end(); ++j)
                {
                    if ((*j)->name == "main" && (*j)->returnType->name == "int32" && (*j)->formals.size() == 0)
                    {
                        main_check = 2;
                        break;
                    }
                    else
                    {
                        main_check = 1;
                    }
                }
            }
            
        }
        if (main_check == 1)
        {
            cout << "Error in class Main : main method wrongly defined." << endl;
            error = 1;
            return error;
        } 
        else if (main_check == 0)
        {
            cout << "Error : class Main missing." << endl;
            error = 1;
            return error;
        }
        for (list<Class *>::iterator i = classes.begin(); i != classes.end(); ++i)
        {
            if((*i)->parent_class != "" && (*i)->parent_class != "Object")
            {
                list<string>::iterator ex = find(names.begin(), names.end(), (*i)->parent_class);
                if(ex == names.end())
                {
                    cout << "Error in class " << (*i)->class_name << " : parent class not defined." << endl;
                    error = 1;
                    return error;
                } else 
                {
                    classAndParent.insert(pair<string, string>((*i)->class_name, (*i)->parent_class));
                } 
            } else 
            {
                classAndParent.insert(pair<string, string>((*i)->class_name, "Object"));
            }
        }
        for (map<string, string>::iterator i = classAndParent.begin(); i != classAndParent.end(); ++i)
        {
            string parent = i->second;
            while (parent != "Object")
            {
                if (parent == i->first)
                {
                    cout << "Error in class " << i->first << " : cycle detected in inheritance." << endl;
                    error = 1;
                    break;
                }
                parent = classAndParent.find(parent)->second;
            }
        }
        return error;
    }

    int general_check()
    {
        
        int error = 0;
        error += checkClassExistence();
        
        for (list<Class *>::iterator i = classes.begin(); i != classes.end(); ++i)
        {
            error += (*i)->general_check(id_map, class_map, (*i)->class_name, classAndParent);
        }
        return error;
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
                cout << ", "<< endl << " ";
                (*i)->print();
            }
        }
        cout << "]" << endl;
    }

    void print_semantic()
    {
        bool first = true;
        cout << "[";
        for (list<Class *>::iterator i = classes.begin(); i != classes.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, class_map, (*i)->class_name);
            }
            else
            {
                cout << ", "<< endl;
                (*i)->print_semantic(id_map, class_map, (*i)->class_name);
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
        cout << "Assign(" << name << ", ";
        expr->print();
        cout << ")";
    }

    int check_assign_type(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if (check_type_id(id_map, name) == "")
        {
            cout << "Error in assign " << name << " : the variable is not defined." << endl;
            error = 1;
        }
        else if (expr->get_type(id_map, classes, self) != check_type_id(id_map, name)){
            cout << "Error in assign " << name << " : the type of the expression should of type " << check_type_id(id_map, name) << " instead of " << expr->get_type(id_map, classes, self) << endl;
            error = 1;
        }
        return error;
    }
    
    string check_type_id(map<string, string> &id_map, string id)
    {
        string type = "";
        map<string, string>::iterator it = id_map.find(id);
        if (it != id_map.end())
        {
            type = it->second;
        }
        return type;
    } 

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return expr->get_type(id_map, classes, self);
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_assign_type(id_map, classes, self);
        error += expr->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "Assign(" << name << ", ";
        expr->print_semantic(id_map, classes, self);
        cout << " : " << expr->get_type(id_map, classes, self) << ")";
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
        cout << "BinOp(" << op << ", ";
        expr1->print();
        cout << ", ";
        expr2->print();
        cout << ")";
    }

    int check_operand_type(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if(op == "and" || op == "or")
        {
            if(expr1->get_type(id_map, classes, self) != "bool" || expr2->get_type(id_map, classes, self) != "bool")
                {
                    cout << "Error in BinOp : operands of "<< op <<" should be bool" << endl;
                    error = 1;
                }
        } 
        else if (op == "=")
        {
            if(expr1->get_type(id_map, classes, self) == "int32" || expr1->get_type(id_map, classes, self) == "bool" || expr1->get_type(id_map, classes, self) == "string" || expr1->get_type(id_map, classes, self) == "unit")
            {
                if (expr2->get_type(id_map, classes, self) != expr1->get_type(id_map, classes, self))
                {
                    cout << "Error in BinOp : operands of "<< op <<" should be of the same type" << endl;
                    error = 1;
                }
                else 
                {
                    if(expr2->get_type(id_map, classes, self) != "int32" && expr2->get_type(id_map, classes, self) != "bool" && expr2->get_type(id_map, classes, self) != "string" && expr2->get_type(id_map, classes, self) != "unit")
                    {
                        cout << "help" << endl;
                        cout << "Error in BinOp : operands of "<< op <<" should be of the same type" << endl;
                        error = 1;
                    }
                }
            } 
            
        } 
        else if(op == "<" || op == ">" || op == "<=" || op == ">=")
        {
            if(expr1->get_type(id_map, classes, self) != "int32" || expr2->get_type(id_map, classes, self) != "int32")
                {
                    cout << "Error in BinOp : operands of "<< op <<" should be int32" << endl;
                    error = 1;
                }
        } 
        else if(op == "+" || op == "-" || op == "*" || op == "/" || op == "^")
        {
            if(expr1->get_type(id_map, classes, self) != "int32" || expr2->get_type(id_map, classes, self) != "int32")
            {
                cout << "Error in BinOp : operands of "<< op <<" should be int32" << endl;
                error = 1;
            }
        }
        return error;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if(op == "and" || op == "or")
        {
            return "bool";
        } 
        else if (op == "=")
        {
            return "bool";
        }
        else if(op == "<" || op == ">" || op == "<=" || op == ">=")
        {
            return "bool";
        } 
        else if(op == "+" || op == "-" || op == "*" || op == "/" || op == "^")
        {
            return "int32";
        }
        else return "";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        
        int error = 0;
        error += check_operand_type(id_map, classes, self);
        error += expr1->general_check(id_map, classes, self);
        error += expr2->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "BinOp(" << op << ", ";
        expr1->print_semantic(id_map, classes, self);
        cout << " : " << expr1->get_type(id_map, classes, self) << ", ";
        expr2->print_semantic(id_map, classes, self);
        cout << " : " << expr2->get_type(id_map, classes, self) << ")";
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
        cout << "UnOp(" << op << ", ";
        expr->print();
        cout << ")";
    }

    int check_operand_type(map<string, string> &id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        if (op == "-")
        {
            if(expr->get_type(id_map, classes, self) != "int32")
            {
                cout << "Error in UnOp : operand of "<< op <<" should be int32" << endl;
                error = 1;
            }
        } else if (op == "not")
        {
            if(expr->get_type(id_map, classes, self) != "bool")
            {
                cout << "Error in UnOp : operand of "<< op <<" should be bool" << endl;
                error = 1;
            }
        }
        return error;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        if(op == "-")
        {
            return "int32";
        } else if (op == "not")
        {
            return "bool";
        } else if(op == "isnull")
        {
            return "bool";
        }
        else return "";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        int error = 0;
        error += check_operand_type(id_map, classes, self);
        error += expr->general_check(id_map, classes, self);
        return error;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "UnOp(" << op << ", ";
        expr->print_semantic(id_map, classes, self);
        cout << " : " << expr->get_type(id_map, classes, self) << ")";
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
    {   args.reverse();
        bool first = true;
        if (objExpr != NULL)
        {
            cout << "Call(";
            objExpr->print();
            cout << ", " << name << ", [";
            for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
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
            cout << "]"
                 << ")";
        }
        else
        {
            cout << "Call(self, " << name << ", [";
            for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
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
            cout << "]"
                 << ")";
        }
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self) // ADD self IN ALL ARGUMENTS
    {

        int error = 0;
        if (objExpr != NULL)
        {
            error += objExpr->general_check(id_map, classes, self);
        }
        args.reverse();
        error += check_method_access(id_map, classes, self);
        error += check_method_args(id_map, classes, self);
        for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
        {
            error += (*i)->general_check(id_map, classes, self);
        }
        return error;
    }

    
    int check_method_args(map<string, string> id_map, map<string, Class*> classes, string self)
    {
        int error = 0;
        string class_name;
        if (objExpr != NULL)
        {
            class_name = objExpr->get_type(id_map, classes, self);
        }
        else
        {
            class_name = self;
        }

        map<string, Class *>::iterator it = classes.find(class_name);
        if (it != classes.end())
        {
            for(list<Method *>::iterator it2 = it->second->Methods.begin(); it2 != it->second->Methods.end(); ++it2)
            {
                if((*it2)->name == name)
                {
                    if ((*it2)->formals.size() != args.size())
                    {
                        cout << "Error in Call : number of arguments in method " << name << " is not correct" << endl;
                        error = 1;
                    }
                    else
                    {
                        list<Expr *>::iterator it3 = args.begin();
                        for (list<Formal *>::iterator it4 = (*it2)->formals.begin(); it4 != (*it2)->formals.end(); ++it4)
                        {
                            if ((*it3)->get_type(id_map, classes, self) != (*it4)->get_type(id_map, classes, self))
                            {
                                cout << "Error in Call : type of argument " << (*it4)->name << " in method " << name << " is not correct" << endl;
                                error = 1;
                            }
                            ++it3;
                        }
                    }
                }
            }
            
        }
        else
        {
            cout << "Error in Call : method " << name << " is not defined in class " << class_name << endl;
            error = 1;
        }
        return error;
    }

    int check_method_access(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
       
        string class_name;
        if (objExpr != NULL)
        {
            class_name = objExpr->get_type(id_map, classes, self);
        }
        else
        {
            class_name = self;
        }
        map<string, Class *>::iterator it = classes.find(class_name);
        if (it != classes.end())
        {
            for(list<Method *>::iterator it2 = it->second->Methods.begin(); it2 != it->second->Methods.end(); ++it2)
            {
                if((*it2)->name == name)
                {
                    return 0;
                }
            }
            return check_method_access_rec(id_map, classes, it->second->parent_class);
        }
        return 1;
    }

    int check_method_access_rec(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string class_name)
    {
        map<string, Class *>::iterator it = classes.find(class_name);
        if (it != classes.end())
        {
            for(list<Method *>::iterator it2 = it->second->Methods.begin(); it2 != it->second->Methods.end(); ++it2)
            {
                if((*it2)->name == name)
                {
                    return 0;
                }
            }
            if (class_name == "Object")
            {
                return 1;
            } else return check_method_access(id_map, classes, it->second->parent_class);
        }
        return 1;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        string class_name;
        if (objExpr != NULL)
        {
            class_name = objExpr->get_type(id_map, classes, self);
        }
        else
        {
            class_name = self;
        }
        map<string, Class *>::iterator it = classes.find(class_name);
        if (it != classes.end())
        {
            for(list<Method *>::iterator it2 = it->second->Methods.begin(); it2 != it->second->Methods.end(); ++it2)
            {
                if((*it2)->name == name)
                {
                    return (*it2)->get_type(id_map, classes, class_name);
                }
            }
            return get_type_rec(id_map, classes, it->second->parent_class);
        }
        
        return "error";
    }

    string get_type_rec(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string class_name)
    {
        map<string, Class *>::iterator it = classes.find(class_name);
        if (it != classes.end())
        {
            for(list<Method *>::iterator it2 = it->second->Methods.begin(); it2 != it->second->Methods.end(); ++it2)
            {
                if((*it2)->name == name)
                {
                    return (*it2)->get_type(id_map, classes, class_name);
                }
            }
            if (class_name == "Object")
            {
                return "error";
            } else return get_type_rec(id_map, classes, it->second->parent_class);
        }
        cout << "help";
        return "error";
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {   
        bool first = true;

        if (objExpr != NULL)
        {
            cout << "Call(";
            objExpr->print_semantic(id_map, classes, self);
            cout << " : " << objExpr->get_type(id_map, classes, self) << ", " << name << ", [";
        }
        else
        {
            cout << "Call(self : "<< self << ", " << name << ", " << endl << "  [";
        }    
        for (list<Expr *>::iterator i = args.begin(); i != args.end(); ++i)
        {
            if (first)
            {
                first = false;
                (*i)->print_semantic(id_map, classes, self);
                cout << " : " << (*i)->get_type(id_map, classes, self);
            }
            else
            {
                cout << ", ";
                (*i)->print_semantic(id_map, classes, self);
                cout << " : " << (*i)->get_type(id_map, classes, self);
            }
        }
        cout << "])";
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

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return "int32";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        print();
    }

};

class String : public Expr
{
    
public:
    string str;

    String(string s)
    {
        str = "\"" + s + "\"";
    }

    void print()
    {
        cout << str ;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return "string";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        print();
    }
};

class Id : public Expr
{

public:
    string str;

    Id(string s)
    {
        str = s;
    }

    void print()
    {
        cout << str ;
    }

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {        
        return check_type_id(id_map, str);
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << str;
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    string check_type_id(map<string, string> &id_map, string str)
    {
        map<string, string>::iterator it = id_map.find(str);
        if (it != id_map.end())
        {
            return it->second;
        }
        else return "error";
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

    string get_type(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return "bool";
    }

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        print();
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

    int general_check(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        return 0;
    }

    void print_semantic(__attribute__ ((unused)) map<string, string> &id_map, __attribute__ ((unused)) map<string, Class*> classes, __attribute__ ((unused)) string self)
    {
        cout << "self";
    }
};