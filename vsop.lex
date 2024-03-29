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
    #include <stack>

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
    string currentString;
    location initPos;
    location loc;
    stack <location> stringLocation;
    stack <location> commentLocation;
%}

    /* Definitions */

low_case [a-z]
up_case [A-Z]
letter {low_case}|{up_case}
digit [0-9]
bin_digit 0|1
hex_digit [a-fA-F0-9]

    /* Identifiers */

objId    [a-z][a-zA-Z_0-9]*
typeId    [A-Z][a-zA-Z_0-9]*
int   [0-9]+
int_hex "0x"{hex_digit}+

    /* Blank */

tab \t 
lf \n
ff \f
cr \r
horizontal_blank (" "|{tab})+
vertical_blank ({lf}|{ff}|{cr})

%x QUOTE COMMENTS MULTICOMMENTS
%%
%{
    // Code run each time yylex is called.
    loc.step();
%}
    /* Rules */

    // string rules, needs ton handle all cases but not the case atm;

"\""        { 
                BEGIN(QUOTE);
                currentString = "";
                stringLocation.push(loc);
                loc.step();
            }

<QUOTE>"\\\"" {
    loc.step();
    currentString += "\\x22";
}

<QUOTE>"\\n" {
    currentString += "\\x0a";
}

<QUOTE>"\\b" {
    loc.step();
    currentString += "\\x08";
}

<QUOTE>"\\t" {
    loc.step();
    currentString += "\\x09";
}

<QUOTE>"\\r" {
    loc.step();
    currentString += "\\x0d";
}

<QUOTE>"\\"({vertical_blank})+({horizontal_blank})* {
    loc.lines();
    loc.columns(yyleng-2);
    loc.step();
}

<QUOTE>"\\\\" {
    loc.step();
    currentString += "\\x5c";
}

<QUOTE>"\\"x{hex_digit}{hex_digit}+ {
    currentString += yytext;
    loc.step();
}

    /* String error handling */

<QUOTE>"\\" {
    print_error(loc.begin,"unvalid escape character in string");
    return Parser::make_YYerror(loc);
}

<QUOTE>{lf} {
    print_error(loc.begin,"unvalid line feed in string");
    return Parser::make_YYerror(loc);
}

<QUOTE><<EOF>> {
    initPos = stringLocation.top();
    stringLocation.pop();
    print_error(initPos.begin, "unclosed double quote");
    BEGIN(INITIAL);
    return Parser::make_YYerror(initPos);
}

<QUOTE>"\\x"{hex_digit}+ {
    print_error(loc.begin,"Wrong escape char \\x and only one hex-digit");
    exit(-1);
    
}

<QUOTE>"\\x" {
    print_error(loc.begin,"Wrong escape char \\x");
    exit(-1);
}

<QUOTE>"\\x"{letter}+ {
    print_error(loc.begin,"Wrong escape char \\x and some letters");
    exit(-1);
}

    /* Other valid characters */

<QUOTE>"\"" {
                BEGIN(INITIAL);
                initPos = stringLocation.top();
                stringLocation.pop();
                loc.step();
                return Parser::make_STRING(currentString,initPos);
}

<QUOTE>.  {
    currentString += yytext;
    loc.step();
}


"//"        { 
                BEGIN(COMMENTS);
            }

<COMMENTS>{vertical_blank}+ {
                BEGIN(INITIAL);
                loc.lines(yyleng); loc.step();
}

<COMMENTS>. {         
}

"(*"        {
                BEGIN(MULTICOMMENTS);
                commentLocation.push(loc);
                loc.step();
}

<MULTICOMMENTS>"(*" {
    commentLocation.push(loc);
    loc.step();
}

<MULTICOMMENTS>{vertical_blank}+{horizontal_blank}* {
    loc.lines();
    loc.columns(yyleng-1);
    loc.step();
}


<MULTICOMMENTS>"*)" {
    commentLocation.pop();
    if(commentLocation.empty()){
        BEGIN(INITIAL);
    }
    loc.step();
}

<MULTICOMMENTS><<EOF>> {
    initPos = commentLocation.top();
    commentLocation.pop();
    print_error(initPos.begin, "unclosed multiline comments");
    BEGIN(INITIAL);
    return Parser::make_YYerror(initPos);
}

<MULTICOMMENTS>. {
}

    /* White spaces */

{horizontal_blank}     loc.step();
{vertical_blank}+      loc.lines(yyleng); loc.step();

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

{int_hex} {
    std::string s = std::to_string(std::stoi(yytext,0,16));
    return make_NUMBER(s,loc);
}
{int_hex}[g-zG-Z]+ {
            print_error(loc.begin, "unvalid int-literal");
            return Parser::make_YYerror(loc);
}
{int}{letter}+ {
            print_error(loc.begin, "unvalid int-literal");
            return Parser::make_YYerror(loc);
}
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
