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
    BOOL        "type-identifier"
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

;

// For some symbols, need to store a value
%token <std::string> OBJECTIDENTIFIER "object-identifier"
%token <std::string> TYPEIDENTIFIER "type-identifier"
%token <int> NUMBER "integer-literal"
%token <std::string> STRING "string-literal"
%token <std::string> type-id 
%token <std::string> object-id   
%token <std::string> init
%token <std::string> formal-aux
%nterm <int> exp

// Precedence
%left "+" "-"; // Could also do: %left PLUS MINUS
%left "*" "/";

%%
// Grammar rules

%start unit;
unit: 
    %empty    {}

program: class { class };

class:          "class" type-id extends "{" class-body;

extends:     "extends" type_id

class-body:     "}" 
                    | field ";" class-body
                    | method class-body;

field:           object-id ":" type init ";";

method:          object-id "(" formals ")" ":" type block;

type:            type-id | "int32" | "bool" | "string" | "unit";

object_id:		OBJECTIDENTIFIER
				| TYPEIDENTIFIER
				{ 
					cout << "syntax error, unexpected type-identifier ";
				};

type_id:		TYPEIDENTIFIER
				| OBJECTIDENTIFIER
				{ 
                    cout << "syntax error, unexpected object-identifier ";
				};

formals:     "(" ")"    
            | formal-aux;

formals-aux:    formal ")"
				| formal "," formals-aux

formal:         object-id ":" type;

block:          "{" expr block-aux "}";

block-aux:      "," expr block-aux;

        expr: "if" expr "then" expr "else" expr 
                | "while" expr "do" expr
                | "let" object-id ":" type "<-" expr "in" expr
                | object-id "<-" expr
                | "not" expr
                | "-" expr
                | "isnull" expr
                | object-id "(" args ")"
                | expr "." object-id "(" args ")"
                | "new" type-id
                | object-id
                | "self"
                | literal
                | "(" ")"
                | "(" expr ")"
                | block;

if: %empty

else: %empty

while: %empty

let: %empty

op:			expr "and" expr
				| expr "or" expr
				| expr "=" expr
				| expr "!=" expr
				| expr "<" expr
				| expr "<=" expr
				| expr ">" expr
				| expr ">=" expr
				| expr "+" expr
				| expr "-" expr
				| expr "*" expr
				| expr "/" expr
				| expr "^" expr
				| expr "mod" expr;


args:           expr args-aux ;

args-aux:   "," expr args-aux;

literal:         "integer-literal" | "string-literal" | boolean-literal;
boolean-literal:        "true" | "false";

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
