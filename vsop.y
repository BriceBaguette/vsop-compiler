/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
 */

%skeleton "lalr1.cc" // -*- C++ -*-
%language "c++"
%require "3.7.5"
%locations

%defines

// Put parser inside a namespace
%define api.namespace {VSOP}

// Give the name of the parser class
%define api.parser.class {Parser}

// Force the token kind enum (used by the lexer) and the symbol kind enum
// (used by the parser) to use the same value for the tokens.
// (e.g. '+' will be represented by the same integer value in both enums.)
%define api.token.raw

// Tokens contain their type, value and location
// Also allow to use the make_TOKEN functions
%define api.token.constructor

// Allow to use C++ objects as semantic values
%define api.value.type variant

// Add some assertions.
%define parse.assert

// C++ code put inside header file
%code requires {
    #include <string>
    #include "ast.hpp"
    namespace VSOP
    {
        class Driver;
    }
}

// Add an argument to the parser constructor
%parse-param {VSOP::Driver &driver}

%code {
    #include "driver.hpp"
    using namespace std;
    list<Field*> fieldtmp;
    list<Method*> methodtmp;
    list<Class*> classtmp;
    list<Formal*> formtmp;
    list<Expr*> exptmp;
    list<Expr*> argtmp;
}

// Token and symbols definitions
%token
    ASSIGN      "<-"
    MINUS       "-"
    PLUS        "+"
    STAR        "*"
    SLASH       "/"
    LPAREN      "("
    RPAREN      ")"
    LBRACE      "{"
    RBRACE      "}"
    COLON       ":"
    SEMICOLON   ";"
    COMMA       ","
    POW         "^"
    DOT         "."
    EQUAL       "="
    LOWER       "<"
    LOWEREQUAL "<="
    IF          "if"
    AND         "and"
    BOOL        "bool"
    CLASS       "class"
    DO          "do"
    ELSE        "else"
    EXTENDS     "extends"
    FALSE       "false"
    IN          "in"
    INT32       "int32"
    ISNULL      "isnull"
    LET         "let"
    NEW         "new"
    NOT         "not"
    SELF        "self"
    STRINGID    "string"
    TRUE        "true"
    THEN        "then"
    UNIT        "unit"
    WHILE       "while"
    START       "start"

;

// For some symbols, need to store a value
%token <std::string> OBJECTIDENTIFIER "object-identifier"
%token <std::string> TYPEIDENTIFIER "type-identifier"
%token <int> NUMBER "integer-literal"
%token <std::string> STRING "string-literal"
%type <Type*> type-id 
%type <std::string> object-id   
%type <BinOp*> bin-op
%type <UnOp*> un-op
%type <Expr*> expr
%type <Block*> block
%type <Expr*> if
%type <Expr*> while
%type <Let*> let
%type <Field*> field
%type <Formal*> formals-aux
%type <Formal*> formal
%type <Type*> type
%type <Expr*> boolean-literal
%type <Expr*> literal
%type <Class*> class
%type <Method*> method
%type <Program*> program

// Precedence
%right ASSIGN;
%left AND;
%right NOT;
%nonassoc EQUAL LOWEREQUAL LOWER;
%left "+" "-"; // Could also do: %left PLUS MINUS
%left "*" "/";
%right ISNULL;
%right POW;
%left DOT;

%precedence "if" "then" "while";
%precedence "else";
%%
// Grammar rules

%start start;
start: 
    program {
        driver.result = $1;
        };

program: program-aux
        {list<Class*> c = classtmp; classtmp.empty(); Program *p = new Program(c); $$ = p;};

program-aux: {}
             | class program-aux
             {classtmp.push_back($1);};

class:      "class" TYPEIDENTIFIER "{" class-body
            {list<Field*> f = fieldtmp; fieldtmp.empty(); list<Method*> m = methodtmp; methodtmp.empty(); Class *c = new Class($2, f, m); $$ = c;}
            | "class" TYPEIDENTIFIER "extends" TYPEIDENTIFIER "{" class-body
            {list<Field*> f = fieldtmp; fieldtmp.empty(); list<Method*> m = methodtmp; methodtmp.empty(); Class *c = new Class($2, $4, f, m); $$ = c;};

class-body:     "}" 
                    | field ";" class-body
                    {fieldtmp.push_back($1);}
                    | method class-body
                    {methodtmp.push_back($1);};

field:          object-id ":" type
                 {Field *f = new Field($1,$3); $$ = f;}
                | object-id ":" type expr
                 {Field *f = new Field($1,$3,$4); $$ = f;};



method:          object-id formals ":" type block
                 {list<Formal*> f = formtmp; formtmp.empty();Method *m = new Method($1, f, $4, $5); $$ = m;};

type:            type-id 
                | "int32" 
                { Type *t = new Type("int32"); $$=t;}
                | "bool" 
                { Type *t = new Type("bool"); $$ = t;}
                | "string" 
                { Type *t = new Type("string"); $$ = t;}
                | "unit"
                { Type *t = new Type("unit"); $$ = t;};

object-id:		OBJECTIDENTIFIER
                {
                   $$ = $1;
                }
				| TYPEIDENTIFIER
				{ 
					cout << "syntax error, unexpected type-identifier ";
				};

type-id:		TYPEIDENTIFIER
                {
                    Type *t = new Type($1); $$ = t;
                }
				| OBJECTIDENTIFIER
				{ 
                    cout << "syntax error, unexpected object-identifier ";
				};

formals:     "(" ")"
            | "(" formals-aux;

formals-aux:    formal ")"
                {formtmp.push_back($1);}
				| formal "," formals-aux
                {formtmp.push_back($1);};

formal:         object-id ":" type
                {Formal *f = new Formal($1, $3); $$ = f;};

block:          "{" expr block-aux
                {list<Expr*> e = exptmp; exptmp.empty(); Block *b = new Block(e); $$=b;};

block-aux:      expr "}"
                {exptmp.push_back($1);}
                | expr block-aux
                {exptmp.push_back($1);};

expr:   if
        | while
        | let
        | object-id "<-" expr
        { Assign *a = new Assign($1, $3); $$ = a;}
        | object-id "(" args
        {list<Expr*> a = argtmp; argtmp.empty(); Call *c = new Call($1, a); $$ = c;}
        | expr "." object-id "(" args 
        {list<Expr*> a = argtmp; argtmp.empty(); Call *c = new Call($3, $1, a); $$ = c;}
        | "new" type-id
        { New *n = new New($2); $$ = n;}
        | object-id
        | "self"
        { Self *s = new Self(); $$ = s;}
        | literal
        | "(" ")"
        {Expr *e = new Expr(); $$ = e;}
        | "(" expr ")"
        {$$ = $2;}
        | block
        | bin-op ";"
        | un-op ";";

if: expr "then" expr
    { If *i = new If($1,$3); $$ = i;}
    | expr "then" expr "else" expr
    { If *i = new If($1,$3,$5); $$ = i;};

while: expr "do" expr
    { While *w = new While($1,$3); $$ = w;};


let: object-id ":" type "in" expr
    { Let *l = new Let($1, $3, $5); $$ = l;}
    | object-id ":" type "<-" expr "in" expr
    { Let *l = new Let($1, $3, $5, $7); $$ = l;};

bin-op:			expr "and" expr
                { BinOp *b = new BinOp($1, "and",$3); $$ = b; }
				| expr "or" expr
                { BinOp *b = new BinOp($1,"or",$3); $$ = b; }
				| expr "=" expr
                { BinOp *b = new BinOp($1,"=",$3); $$ = b; }
				| expr "!=" expr
                { BinOp *b = new BinOp($1,"!=",$3); $$ = b; }
				| expr "<" expr
                { BinOp *b = new BinOp($1,"<",$3); $$ = b; }
				| expr "<=" expr
                { BinOp *b = new BinOp($1,"<=",$3); $$ = b ;}
				| expr ">" expr
                { BinOp *b = new BinOp($1,">",$3); $$ = b; }
				| expr ">=" expr
                { BinOp *b = new BinOp($1,">=",$3); $$ = b; }
				| expr "+" expr
                { BinOp *b = new BinOp($1,"+",$3); $$ = b; }
				| expr "-" expr
                { BinOp *b = new BinOp($1,"-",$3); $$ = b; }
				| expr "*" expr
                { BinOp *b = new BinOp($1,"*",$3); $$ = b; }
				| expr "/" expr
                { BinOp *b = new BinOp($1,"/",$3); $$ = b; }
				| expr "^" expr
                { BinOp *b = new BinOp($1,"^",$3); $$ = b; };

un-op:          "not" expr
                {UnOp *u = new UnOp("not", $2); $$ = u; }
                | "-" expr
                {UnOp *u = new UnOp("-", $2); $$ = u;}
                | "isnull" expr
                {UnOp *u = new UnOp("isnull", $2); $$ = u;};

args:       expr ")" 
                {argtmp.push_back($1);}
            | expr "," args
                {argtmp.push_back($1);};

literal:         NUMBER 
                {$$ = new Number($1);}
                | STRING
                {$$ = new String($1);}
                | boolean-literal;
boolean-literal:        "true" 
                        {$$ = new Bool("true");}
                        | "false"
                        {$$ = new Bool("false");};

%%
// User code
void VSOP::Parser::error(const location_type& l, const std::string& m)
{
    const position &pos = l.begin;

    cerr << *(pos.filename) << ","
         << pos.line << "," 
         << pos.column << ","
         << m
         << endl;
}
