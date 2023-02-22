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
%nterm <int> exp

// Precedence
%left "+" "-"; // Could also do: %left PLUS MINUS
%left "*" "/";

%%
// Grammar rules

%start unit;
unit: 
    %empty    {}
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
