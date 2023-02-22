    /* This flex/bison example is provided to you as a starting point for your
     * assignment. You are free to use its code in your project.
     *
     * This example implements a simple calculator. You can use the '-l' flag to
     * list all the tokens found in the source file, and the '-p' flag (or no flag)
     * to parse the file and to compute the result.
     *
     * Also, if you have any suggestions for improvements, please let us know.
     */

%{
    /* Includes */
    #include <string>

    #include "parser.hpp"
    #include "driver.hpp"
%}

    /* Flex options
     * - noyywrap: yylex will not call yywrap() function
     * - nounput: do not generate yyunput() function
     * - noinput: do not generate yyinput() function
     * - batch: tell Flex that the lexer will not often be used interactively
     */
%option noyywrap nounput noinput batch

%{
    /* Code to include at the beginning of the lexer file. */
    using namespace std;
    using namespace VSOP;

    // Create a new NUMBER token from the value s.
    Parser::symbol_type make_NUMBER(const string &s,
                                    const location &loc);

    // Print an lexical error message.
    static void print_error(const position &pos,
                            const string &m);

    // Code run each time a pattern is matched.
    #define YY_USER_ACTION  loc.columns(yyleng);

    // Global variable used to maintain the current location.
    location loc;
%}

    /* Definitions */
objId    [a-z][a-zA-Z_0-9]*
typeId    [A-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%%
%{
    // Code run each time yylex is called.
    loc.step();
%}
    /* Rules */



    /* White spaces */
{blank}+    loc.step();
\n+         loc.lines(yyleng); loc.step();

    /* Operators */
"-"         return Parser::make_MINUS(loc);
"+"         return Parser::make_PLUS(loc);
"*"         return Parser::make_STAR(loc);
"/"         return Parser::make_SLASH(loc);
"("         return Parser::make_LPAREN(loc);
")"         return Parser::make_RPAREN(loc);
"<-"        return Parser::make_ASSIGN(loc);
"{"         return Parser::make_LBRACE(loc);
"}"         return Parser::make_RBRACE(loc);
":"         return Parser::make_COLON(loc);
";"         return Parser::make_SEMICOLON(loc);
","         return Parser::make_COMMA(loc);
"^"         return Parser::make_POW(loc);
"."         return Parser::make_DOT(loc);
"="         return Parser::make_EQUAL(loc);
"<"         return Parser::make_LOWER(loc);
"<="        return Parser::make_LOWEREQUAL(loc);

    /* Keywords */
"and"       return Parser::make_AND(loc);
"bool"      return Parser::make_BOOL(loc);
"class"     return Parser::make_CLASS(loc);
"do"        return Parser::make_DO(loc);
"else"      return Parser::make_ELSE(loc);
"extends"   return Parser::make_EXTENDS(loc);
"false"     return Parser::make_FALSE(loc);
"if"        return Parser::make_IF(loc);
"in"        return Parser::make_IN(loc);
"int32"     return Parser::make_INT32(loc);
"isnull"    return Parser::make_ISNULL(loc);
"let"       return Parser::make_LET(loc);
"new"       return Parser::make_NEW(loc);
"not"       return Parser::make_NOT(loc);
"self"      return Parser::make_SELF(loc);
"string"    return Parser::make_STRINGID(loc);
"then"      return Parser::make_THEN(loc);
"true"      return Parser::make_TRUE(loc);
"unit"      return Parser::make_UNIT(loc);
"while"     return Parser::make_WHILE(loc);

    /* Numbers and identifiers */

{int}       return make_NUMBER(yytext, loc);
{objId}     return Parser::make_OBJECTIDENTIFIER(yytext, loc);
{typeId}    return Parser::make_TYPEIDENTIFIER(yytext, loc);

    /* Invalid characters */
.           {
                print_error(loc.begin, "invalid character: " + string(yytext));
                return Parser::make_YYerror(loc);
}
    
    /* End of file */
<<EOF>>     return Parser::make_YYEOF(loc);
%%

    /* User code */

Parser::symbol_type make_NUMBER(const string &s,
                                const location& loc)
{
    int n = stoi(s);

    return Parser::make_NUMBER(n, loc);
}

static void print_error(const position &pos, const string &m)
{
    cerr << *(pos.filename) << ":"
         << pos.line << ":"
         << pos.column << ":"
         << " lexical error: "
         << m
         << endl;
}

void Driver::scan_begin()
{
    loc.initialize(&source_file);

    if (source_file.empty() || source_file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(source_file.c_str(), "r")))
    {
        cerr << "cannot open " << source_file << ": " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
}

void Driver::scan_end()
{
    fclose(yyin);
}
