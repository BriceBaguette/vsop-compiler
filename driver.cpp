/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
 */

#include <iostream>
#include <string>
#include <map>

#include "driver.hpp"
#include "parser.hpp"

using namespace std;
using namespace VSOP;

/**
 * @brief Map a token type to a string.
 */
static const map<Parser::token_type, string> type_to_string = {
    {Parser::token::ASSIGN, "assign"},
    {Parser::token::MINUS, "minus"},
    {Parser::token::PLUS, "plus"},
    {Parser::token::STAR, "star"},
    {Parser::token::SLASH, "slash"},
    {Parser::token::LPAREN, "lpar"},
    {Parser::token::RPAREN, "rpar"},
    {Parser::token::OBJECTIDENTIFIER, "object-identifier"},
    {Parser::token::TYPEIDENTIFIER, "type-identifier"},
    {Parser::token::NUMBER, "number"},
    {Parser::token::AND, "and"},
    {Parser::token::BOOL, "bool"},
    {Parser::token::CLASS, "class"},
    {Parser::token::COLON, "colon"},
    {Parser::token::COMMA, "comma"},
    {Parser::token::DO, "do"},
    {Parser::token::DOT, "dot"},
    {Parser::token::ELSE, "else"},
    {Parser::token::EQUAL, "equal"},
    {Parser::token::EXTENDS, "extends"},
    {Parser::token::FALSE, "false"},
    {Parser::token::IF, "if"},
    {Parser::token::IN, "in"},
    {Parser::token::INT32, "int32"},
    {Parser::token::ISNULL, "isnull"},
    {Parser::token::LBRACE, "lbrace"},
    {Parser::token::LET, "let"},
    {Parser::token::LOWER, "lower"},
    {Parser::token::LOWEREQUAL, "lower-equal"},
    {Parser::token::NEW, "new"},
    {Parser::token::NOT, "not"},
    {Parser::token::POW, "pow"},
    {Parser::token::RBRACE, "rbrace"},
    {Parser::token::SELF, "self"},
    {Parser::token::SEMICOLON, "semi-colon"},
    {Parser::token::STRINGID, "string"},
    {Parser::token::THEN, "then"},
    {Parser::token::TRUE, "true"},
    {Parser::token::UNIT, "unit"},
    {Parser::token::WHILE, "while"},

};

/**
 * @brief Print the information about a token
 *
 * @param token the token
 */
static void print_token(Parser::symbol_type token)
{
    position pos = token.location.begin;
    Parser::token_type type = (Parser::token_type)token.type_get();

    cout << pos.line << ","
         << pos.column << ","
         << type_to_string.at(type);

    switch (type)
    {
    case Parser::token::NUMBER:
    {
        int value = token.value.as<int>();
        cout << "," << value;
        break;
    }

    case Parser::token::TYPEIDENTIFIER:
    {
        string id = token.value.as<string>();
        cout << "," << id;
        break;
    }

    case Parser::token::OBJECTIDENTIFIER:
    {
        string id = token.value.as<string>();
        cout << "," << id;
        break;
    }

    case Parser::token::STRING:
    {
        string id = token.value.as<string>();
        cout << "," << "\"" << id << "\"";
        break;
    }


    default:
        break;
    }

    cout << endl;
}

int Driver::lex()
{
    scan_begin();

    int error = 0;

    while (true)
    {
        Parser::symbol_type token = yylex();

        if ((Parser::token_type)token.type_get() == Parser::token::YYEOF)
            break;

        if ((Parser::token_type)token.type_get() != Parser::token::YYerror)
            tokens.push_back(token);

        else
            error = 1;
    }

    scan_end();

    return error;
}

int Driver::parse()
{
    scan_begin();

    parser = new Parser(*this);

    int res = parser->parse();
    scan_end();

    delete parser;

    return res;
}

void Driver::print_tokens()
{
    for (auto token : tokens)
        print_token(token);
}
