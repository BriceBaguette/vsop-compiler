// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 52 "vsop.y"

    #include "driver.hpp"
    using namespace std;
    list<Field*> fieldtmp;
    list<Method*> methodtmp;
    list<Class*> classtmp;
    list<Formal*> formtmp;
    list<Expr*> exptmp;
    list<Expr*> argtmp;

#line 57 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 19 "vsop.y"
namespace VSOP {
#line 150 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (VSOP::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_69_bin_op: // bin-op
        value.YY_MOVE_OR_COPY< BinOp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< Block* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.YY_MOVE_OR_COPY< Class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_73_boolean_literal: // boolean-literal
        value.YY_MOVE_OR_COPY< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.YY_MOVE_OR_COPY< Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< Formal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.YY_MOVE_OR_COPY< Method* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_59_type_id: // type-id
        value.YY_MOVE_OR_COPY< Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_70_un_op: // un-op
        value.YY_MOVE_OR_COPY< UnOp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "integer-literal"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OBJECTIDENTIFIER: // "object-identifier"
      case symbol_kind::S_TYPEIDENTIFIER: // "type-identifier"
      case symbol_kind::S_STRING: // "string-literal"
      case symbol_kind::S_58_object_id: // object-id
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_69_bin_op: // bin-op
        value.move< BinOp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< Block* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class: // class
        value.move< Class* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_73_boolean_literal: // boolean-literal
        value.move< Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field: // field
        value.move< Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< Formal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_method: // method
        value.move< Method* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_59_type_id: // type-id
        value.move< Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_70_un_op: // un-op
        value.move< UnOp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "integer-literal"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OBJECTIDENTIFIER: // "object-identifier"
      case symbol_kind::S_TYPEIDENTIFIER: // "type-identifier"
      case symbol_kind::S_STRING: // "string-literal"
      case symbol_kind::S_58_object_id: // object-id
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_69_bin_op: // bin-op
        value.copy< BinOp* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< Block* > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.copy< Class* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_73_boolean_literal: // boolean-literal
        value.copy< Expr* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.copy< Field* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< Formal* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.copy< Method* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Program* > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_59_type_id: // type-id
        value.copy< Type* > (that.value);
        break;

      case symbol_kind::S_70_un_op: // un-op
        value.copy< UnOp* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "integer-literal"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_OBJECTIDENTIFIER: // "object-identifier"
      case symbol_kind::S_TYPEIDENTIFIER: // "type-identifier"
      case symbol_kind::S_STRING: // "string-literal"
      case symbol_kind::S_58_object_id: // object-id
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_69_bin_op: // bin-op
        value.move< BinOp* > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< Block* > (that.value);
        break;

      case symbol_kind::S_class: // class
        value.move< Class* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_73_boolean_literal: // boolean-literal
        value.move< Expr* > (that.value);
        break;

      case symbol_kind::S_field: // field
        value.move< Field* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< Formal* > (that.value);
        break;

      case symbol_kind::S_method: // method
        value.move< Method* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Program* > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_59_type_id: // type-id
        value.move< Type* > (that.value);
        break;

      case symbol_kind::S_70_un_op: // un-op
        value.move< UnOp* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "integer-literal"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_OBJECTIDENTIFIER: // "object-identifier"
      case symbol_kind::S_TYPEIDENTIFIER: // "type-identifier"
      case symbol_kind::S_STRING: // "string-literal"
      case symbol_kind::S_58_object_id: // object-id
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_69_bin_op: // bin-op
        yylhs.value.emplace< BinOp* > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< Block* > ();
        break;

      case symbol_kind::S_class: // class
        yylhs.value.emplace< Class* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_if: // if
      case symbol_kind::S_while: // while
      case symbol_kind::S_let: // let
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_73_boolean_literal: // boolean-literal
        yylhs.value.emplace< Expr* > ();
        break;

      case symbol_kind::S_field: // field
        yylhs.value.emplace< Field* > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< Formal* > ();
        break;

      case symbol_kind::S_method: // method
        yylhs.value.emplace< Method* > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Program* > ();
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_59_type_id: // type-id
        yylhs.value.emplace< Type* > ();
        break;

      case symbol_kind::S_70_un_op: // un-op
        yylhs.value.emplace< UnOp* > ();
        break;

      case symbol_kind::S_NUMBER: // "integer-literal"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_OBJECTIDENTIFIER: // "object-identifier"
      case symbol_kind::S_TYPEIDENTIFIER: // "type-identifier"
      case symbol_kind::S_STRING: // "string-literal"
      case symbol_kind::S_58_object_id: // object-id
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // start: program
#line 151 "vsop.y"
            {
        driver.result = yystack_[0].value.as < Program* > ();
        }
#line 831 "parser.cpp"
    break;

  case 3: // program: program-aux
#line 156 "vsop.y"
        {list<Class*> c = classtmp; classtmp.clear(); Program *p = new Program(c); yylhs.value.as < Program* > () = p;}
#line 837 "parser.cpp"
    break;

  case 4: // program-aux: %empty
#line 158 "vsop.y"
             {}
#line 843 "parser.cpp"
    break;

  case 5: // program-aux: class program-aux
#line 160 "vsop.y"
             {classtmp.push_back(yystack_[1].value.as < Class* > ());}
#line 849 "parser.cpp"
    break;

  case 6: // class: "class" "type-identifier" "{" class-body
#line 163 "vsop.y"
            {list<Field*> f = fieldtmp; fieldtmp.clear(); list<Method*> m = methodtmp; methodtmp.clear(); Class *c = new Class(yystack_[2].value.as < std::string > (), f, m); yylhs.value.as < Class* > () = c;}
#line 855 "parser.cpp"
    break;

  case 7: // class: "class" "type-identifier" "extends" "type-identifier" "{" class-body
#line 165 "vsop.y"
            {list<Field*> f = fieldtmp; fieldtmp.clear(); list<Method*> m = methodtmp; methodtmp.clear(); Class *c = new Class(yystack_[4].value.as < std::string > (), yystack_[2].value.as < std::string > (), f, m); yylhs.value.as < Class* > () = c;}
#line 861 "parser.cpp"
    break;

  case 9: // class-body: field ";" class-body
#line 169 "vsop.y"
                    {fieldtmp.push_back(yystack_[2].value.as < Field* > ());}
#line 867 "parser.cpp"
    break;

  case 10: // class-body: method class-body
#line 171 "vsop.y"
                    {methodtmp.push_back(yystack_[1].value.as < Method* > ());}
#line 873 "parser.cpp"
    break;

  case 11: // field: object-id ":" type
#line 174 "vsop.y"
                 {Field *f = new Field(yystack_[2].value.as < std::string > (),yystack_[0].value.as < Type* > ()); yylhs.value.as < Field* > () = f;}
#line 879 "parser.cpp"
    break;

  case 12: // field: object-id ":" type "<-" expr
#line 176 "vsop.y"
                 {Field *f = new Field(yystack_[4].value.as < std::string > (),yystack_[2].value.as < Type* > (),yystack_[0].value.as < Expr* > ()); yylhs.value.as < Field* > () = f;}
#line 885 "parser.cpp"
    break;

  case 13: // method: object-id formals ":" type block
#line 181 "vsop.y"
                 {list<Formal*> f = formtmp; formtmp.clear(); Method *m = new Method(yystack_[4].value.as < std::string > (), f, yystack_[1].value.as < Type* > (), yystack_[0].value.as < Block* > ()); yylhs.value.as < Method* > () = m;}
#line 891 "parser.cpp"
    break;

  case 14: // type: type-id
#line 183 "vsop.y"
                 { yylhs.value.as < Type* > () = yystack_[0].value.as < Type* > (); }
#line 897 "parser.cpp"
    break;

  case 15: // type: "int32"
#line 185 "vsop.y"
                { Type *t = new Type("int32"); yylhs.value.as < Type* > ()=t;}
#line 903 "parser.cpp"
    break;

  case 16: // type: "bool"
#line 187 "vsop.y"
                { Type *t = new Type("bool"); yylhs.value.as < Type* > () = t;}
#line 909 "parser.cpp"
    break;

  case 17: // type: "string"
#line 189 "vsop.y"
                { Type *t = new Type("string"); yylhs.value.as < Type* > () = t;}
#line 915 "parser.cpp"
    break;

  case 18: // type: "unit"
#line 191 "vsop.y"
                { Type *t = new Type("unit"); yylhs.value.as < Type* > () = t;}
#line 921 "parser.cpp"
    break;

  case 19: // object-id: "object-identifier"
#line 194 "vsop.y"
                {
                   yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
                }
#line 929 "parser.cpp"
    break;

  case 20: // type-id: "type-identifier"
#line 200 "vsop.y"
                {
                    Type *t = new Type(yystack_[0].value.as < std::string > ()); yylhs.value.as < Type* > () = t;
                }
#line 937 "parser.cpp"
    break;

  case 23: // formals-aux: formal ")"
#line 208 "vsop.y"
                {formtmp.push_back(yystack_[1].value.as < Formal* > ());}
#line 943 "parser.cpp"
    break;

  case 24: // formals-aux: formal "," formals-aux
#line 210 "vsop.y"
                {formtmp.push_back(yystack_[2].value.as < Formal* > ());}
#line 949 "parser.cpp"
    break;

  case 25: // formal: object-id ":" type
#line 213 "vsop.y"
                {Formal *f = new Formal(yystack_[2].value.as < std::string > (), yystack_[0].value.as < Type* > ()); yylhs.value.as < Formal* > () = f;}
#line 955 "parser.cpp"
    break;

  case 26: // block: "{" block-aux
#line 216 "vsop.y"
                {list<Expr*> e = exptmp; exptmp.clear(); Block *b = new Block(e); yylhs.value.as < Block* > ()=b;}
#line 961 "parser.cpp"
    break;

  case 27: // block-aux: expr "}"
#line 219 "vsop.y"
                {exptmp.push_back(yystack_[1].value.as < Expr* > ());}
#line 967 "parser.cpp"
    break;

  case 28: // block-aux: expr ";" block-aux
#line 221 "vsop.y"
                {exptmp.push_back(yystack_[2].value.as < Expr* > ());}
#line 973 "parser.cpp"
    break;

  case 29: // expr: if
#line 224 "vsop.y"
        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 979 "parser.cpp"
    break;

  case 30: // expr: while
#line 226 "vsop.y"
        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 985 "parser.cpp"
    break;

  case 31: // expr: let
#line 228 "vsop.y"
        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 991 "parser.cpp"
    break;

  case 32: // expr: object-id "<-" expr
#line 230 "vsop.y"
        { Assign *a = new Assign(yystack_[2].value.as < std::string > (), yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = a;}
#line 997 "parser.cpp"
    break;

  case 33: // expr: object-id "(" args
#line 232 "vsop.y"
        {list<Expr*> a = argtmp; argtmp.clear(); Call *c = new Call(yystack_[2].value.as < std::string > (), a); yylhs.value.as < Expr* > () = c;}
#line 1003 "parser.cpp"
    break;

  case 34: // expr: expr "." object-id "(" args
#line 234 "vsop.y"
        {list<Expr*> a = argtmp; argtmp.clear(); Call *c = new Call(yystack_[2].value.as < std::string > (), yystack_[4].value.as < Expr* > (), a); yylhs.value.as < Expr* > () = c;}
#line 1009 "parser.cpp"
    break;

  case 35: // expr: "new" type-id
#line 236 "vsop.y"
        { New *n = new New(yystack_[0].value.as < Type* > ()); yylhs.value.as < Expr* > () = n;}
#line 1015 "parser.cpp"
    break;

  case 36: // expr: object-id
#line 238 "vsop.y"
        {Expr *e = new Id(yystack_[0].value.as < std::string > ()); yylhs.value.as < Expr* > () = e;}
#line 1021 "parser.cpp"
    break;

  case 37: // expr: "self"
#line 240 "vsop.y"
        { Self *s = new Self(); yylhs.value.as < Expr* > () = s;}
#line 1027 "parser.cpp"
    break;

  case 38: // expr: literal
#line 242 "vsop.y"
        {yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > ();}
#line 1033 "parser.cpp"
    break;

  case 39: // expr: "(" ")"
#line 244 "vsop.y"
        {Expr *e = new Expr(); yylhs.value.as < Expr* > () = e;}
#line 1039 "parser.cpp"
    break;

  case 40: // expr: "(" expr ")"
#line 246 "vsop.y"
        {yylhs.value.as < Expr* > () = yystack_[1].value.as < Expr* > ();}
#line 1045 "parser.cpp"
    break;

  case 41: // expr: block
#line 248 "vsop.y"
        { yylhs.value.as < Expr* > () = yystack_[0].value.as < Block* > (); }
#line 1051 "parser.cpp"
    break;

  case 42: // expr: bin-op
#line 250 "vsop.y"
        {yylhs.value.as < Expr* > () = yystack_[0].value.as < BinOp* > ();}
#line 1057 "parser.cpp"
    break;

  case 43: // expr: un-op
#line 252 "vsop.y"
        {yylhs.value.as < Expr* > () = yystack_[0].value.as < UnOp* > ();}
#line 1063 "parser.cpp"
    break;

  case 44: // if: "if" expr "then" expr
#line 255 "vsop.y"
    { If *i = new If(yystack_[2].value.as < Expr* > (),yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = i;}
#line 1069 "parser.cpp"
    break;

  case 45: // if: "if" expr "then" expr "else" expr
#line 257 "vsop.y"
    { If *i = new If(yystack_[4].value.as < Expr* > (),yystack_[2].value.as < Expr* > (),yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = i;}
#line 1075 "parser.cpp"
    break;

  case 46: // while: "while" expr "do" expr
#line 260 "vsop.y"
    { While *w = new While(yystack_[2].value.as < Expr* > (),yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = w;}
#line 1081 "parser.cpp"
    break;

  case 47: // let: "let" object-id ":" type "in" expr
#line 264 "vsop.y"
    { Let *l = new Let(yystack_[4].value.as < std::string > (), yystack_[2].value.as < Type* > (), yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = l;}
#line 1087 "parser.cpp"
    break;

  case 48: // let: "let" object-id ":" type "<-" expr "in" expr
#line 266 "vsop.y"
    { Let *l = new Let(yystack_[6].value.as < std::string > (), yystack_[4].value.as < Type* > (), yystack_[2].value.as < Expr* > (), yystack_[0].value.as < Expr* > ()); yylhs.value.as < Expr* > () = l;}
#line 1093 "parser.cpp"
    break;

  case 49: // bin-op: expr "and" expr
#line 269 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (), "and",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1099 "parser.cpp"
    break;

  case 50: // bin-op: expr "or" expr
#line 271 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"or",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1105 "parser.cpp"
    break;

  case 51: // bin-op: expr "=" expr
#line 273 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"=",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1111 "parser.cpp"
    break;

  case 52: // bin-op: expr "!=" expr
#line 275 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"!=",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1117 "parser.cpp"
    break;

  case 53: // bin-op: expr "<" expr
#line 277 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"<",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1123 "parser.cpp"
    break;

  case 54: // bin-op: expr "<=" expr
#line 279 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"<=",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b ;}
#line 1129 "parser.cpp"
    break;

  case 55: // bin-op: expr ">" expr
#line 281 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),">",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1135 "parser.cpp"
    break;

  case 56: // bin-op: expr ">=" expr
#line 283 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),">=",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1141 "parser.cpp"
    break;

  case 57: // bin-op: expr "+" expr
#line 285 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"+",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1147 "parser.cpp"
    break;

  case 58: // bin-op: expr "-" expr
#line 287 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"-",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1153 "parser.cpp"
    break;

  case 59: // bin-op: expr "*" expr
#line 289 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"*",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1159 "parser.cpp"
    break;

  case 60: // bin-op: expr "/" expr
#line 291 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"/",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1165 "parser.cpp"
    break;

  case 61: // bin-op: expr "^" expr
#line 293 "vsop.y"
                { BinOp *b = new BinOp(yystack_[2].value.as < Expr* > (),"^",yystack_[0].value.as < Expr* > ()); yylhs.value.as < BinOp* > () = b; }
#line 1171 "parser.cpp"
    break;

  case 62: // un-op: "not" expr
#line 296 "vsop.y"
                {UnOp *u = new UnOp("not", yystack_[0].value.as < Expr* > ()); yylhs.value.as < UnOp* > () = u; }
#line 1177 "parser.cpp"
    break;

  case 63: // un-op: "-" expr
#line 298 "vsop.y"
                {UnOp *u = new UnOp("-", yystack_[0].value.as < Expr* > ()); yylhs.value.as < UnOp* > () = u;}
#line 1183 "parser.cpp"
    break;

  case 64: // un-op: "isnull" expr
#line 300 "vsop.y"
                {UnOp *u = new UnOp("isnull", yystack_[0].value.as < Expr* > ()); yylhs.value.as < UnOp* > () = u;}
#line 1189 "parser.cpp"
    break;

  case 66: // args: expr ")"
#line 304 "vsop.y"
                {argtmp.push_back(yystack_[1].value.as < Expr* > ());}
#line 1195 "parser.cpp"
    break;

  case 67: // args: expr "," args
#line 306 "vsop.y"
                {argtmp.push_back(yystack_[2].value.as < Expr* > ());}
#line 1201 "parser.cpp"
    break;

  case 68: // literal: "integer-literal"
#line 309 "vsop.y"
                {yylhs.value.as < Expr* > () = new Number(yystack_[0].value.as < int > ());}
#line 1207 "parser.cpp"
    break;

  case 69: // literal: "string-literal"
#line 311 "vsop.y"
                {yylhs.value.as < Expr* > () = new String(yystack_[0].value.as < std::string > ());}
#line 1213 "parser.cpp"
    break;

  case 70: // literal: boolean-literal
#line 312 "vsop.y"
                  { yylhs.value.as < Expr* > () = yystack_[0].value.as < Expr* > (); }
#line 1219 "parser.cpp"
    break;

  case 71: // boolean-literal: "true"
#line 314 "vsop.y"
                        {yylhs.value.as < Expr* > () = new Bool("true");}
#line 1225 "parser.cpp"
    break;

  case 72: // boolean-literal: "false"
#line 316 "vsop.y"
                        {yylhs.value.as < Expr* > () = new Bool("false");}
#line 1231 "parser.cpp"
    break;


#line 1235 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char Parser::yypact_ninf_ = -98;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      -6,   -22,    22,   -98,   -98,    -6,     0,   -98,   -98,    -3,
      -7,   -98,   -98,   -98,    34,    -3,    29,    47,    -3,   -98,
      19,   382,    60,    -3,   -98,   -98,    61,   -98,     4,   -98,
     -98,   -98,   -98,   -98,    71,   -98,   382,   -98,   382,   -98,
      35,   369,    68,   -98,   -98,   369,   316,   369,   369,   -98,
     369,    35,    42,   369,   -98,   -98,   369,   -98,   -98,    13,
     -98,   269,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
      17,   -98,   127,   -98,    64,   145,    92,    74,   -98,   287,
     179,   369,   354,   369,   369,   369,   369,   369,    35,   369,
     369,   369,   369,   369,   369,   369,   369,   -98,   -98,   369,
     369,   382,   369,   269,   -98,   109,   -98,    17,    17,    92,
      92,    92,    82,   292,   292,   292,   287,   269,   269,   269,
     269,   -98,   213,    -1,   269,   -98,   354,   354,   369,   369,
     369,   -98,   -98,   269,   235,   269,   369,   269
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     0,     2,     3,     4,     0,     1,     5,     0,
       0,     8,    19,     6,     0,     0,     0,     0,     0,    10,
       0,     0,     0,     0,     9,    21,     0,    22,     0,    16,
      15,    17,    18,    20,    11,    14,     0,     7,     0,    23,
       0,     0,     0,    25,    24,     0,     0,     0,     0,    72,
       0,     0,     0,     0,    37,    71,     0,    68,    69,    36,
      41,    12,    29,    30,    31,    42,    43,    38,    70,    13,
      63,    39,     0,    26,     0,     0,    64,     0,    35,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    40,    27,     0,
       0,     0,     0,    32,    65,     0,    33,    58,    57,    59,
      60,    61,     0,    51,    53,    54,    49,    50,    52,    55,
      56,    28,    44,     0,    46,    66,     0,     0,     0,     0,
       0,    67,    34,    45,     0,    47,     0,    48
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -98,   -98,   -98,    86,   -98,    -4,   -98,   -98,   -35,    16,
      40,   -98,    53,   -98,    52,    -2,   -41,   -98,   -98,   -98,
     -98,   -98,   -97,   -98,   -98
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,     5,    13,    14,    15,    34,    59,
      35,    22,    27,    28,    60,    73,   105,    62,    63,    64,
      65,    66,   106,    67,    68
  };

  const short
  Parser::yytable_[] =
  {
      61,    42,   129,    43,    70,    72,    74,    75,    11,    76,
       9,    19,    79,    39,    24,    80,    81,     1,    40,    37,
       6,    82,     7,    85,    86,    16,    10,   130,    25,   131,
     132,    16,    87,    88,    16,    17,    26,    20,    12,    16,
     103,    21,   107,   108,   109,   110,   111,    18,   113,   114,
     115,   116,   117,   118,   119,   120,    26,    23,    74,   122,
      12,   124,    93,    94,    95,    96,   123,    77,    83,    84,
      85,    86,    36,    38,    41,    98,    12,    99,    47,    87,
      88,    89,    90,    91,    33,    92,   101,   133,   134,   135,
     127,     8,    78,    44,    69,   137,     0,   121,     0,     0,
       0,     0,     0,     0,   112,     0,     0,    87,    88,    93,
      94,    95,    96,    83,    84,    85,    86,     0,   125,     0,
       0,     0,     0,   126,    87,    88,    89,    90,    91,     0,
      92,    83,    84,    85,    86,     0,    97,    93,    94,    95,
      96,     0,    87,    88,    89,    90,    91,     0,    92,    83,
      84,    85,    86,     0,    93,    94,    95,    96,     0,     0,
      87,    88,    89,    90,    91,     0,    92,     0,     0,     0,
       0,     0,    93,    94,    95,    96,     0,     0,     0,     0,
       0,     0,   100,    83,    84,    85,    86,     0,     0,     0,
      93,    94,    95,    96,    87,    88,    89,    90,    91,     0,
      92,     0,     0,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,    84,    85,
      86,     0,     0,     0,    93,    94,    95,    96,    87,    88,
      89,    90,    91,     0,    92,     0,     0,     0,   128,    83,
      84,    85,    86,     0,     0,     0,     0,     0,     0,     0,
      87,    88,    89,    90,    91,     0,    92,     0,    93,    94,
      95,    96,     0,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,    84,    85,    86,     0,     0,     0,
      93,    94,    95,    96,    87,    88,    89,    90,    91,     0,
      92,    83,    84,    85,    86,     0,    83,    84,    85,    86,
       0,     0,    87,    88,    89,    90,    91,    87,    88,    -1,
      -1,    -1,     0,     0,    93,    94,    95,    96,     0,     0,
      45,     0,     0,     0,    46,    71,    47,     0,     0,     0,
       0,     0,    93,    94,    95,    96,    48,    93,    94,    95,
      96,     0,     0,    49,     0,     0,    50,    51,    52,    53,
      54,     0,    55,     0,     0,    56,     0,    12,    45,    57,
      58,     0,    46,   104,    47,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    48,     0,     0,    46,     0,    47,
       0,    49,     0,     0,    50,    51,    52,    53,    54,    48,
      55,     0,     0,    56,     0,    12,    49,    57,    58,    50,
      51,    52,    53,    54,    29,    55,     0,     0,    56,     0,
      12,    30,    57,    58,     0,     0,     0,    31,     0,     0,
      32,     0,     0,     0,    33
  };

  const short
  Parser::yycheck_[] =
  {
      41,    36,     3,    38,    45,    46,    47,    48,    11,    50,
      10,    15,    53,     9,    18,    56,     3,    23,    14,    23,
      42,     8,     0,     6,     7,     9,    26,    28,     9,   126,
     127,    15,    15,    16,    18,    42,    20,     8,    41,    23,
      81,    12,    83,    84,    85,    86,    87,    13,    89,    90,
      91,    92,    93,    94,    95,    96,    40,    10,    99,   100,
      41,   102,    45,    46,    47,    48,   101,    51,     4,     5,
       6,     7,    12,    12,     3,    11,    41,    13,    10,    15,
      16,    17,    18,    19,    42,    21,    12,   128,   129,   130,
       8,     5,    52,    40,    42,   136,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    15,    16,    45,
      46,    47,    48,     4,     5,     6,     7,    -1,     9,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    19,    -1,
      21,     4,     5,     6,     7,    -1,     9,    45,    46,    47,
      48,    -1,    15,    16,    17,    18,    19,    -1,    21,     4,
       5,     6,     7,    -1,    45,    46,    47,    48,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    37,     4,     5,     6,     7,    -1,    -1,    -1,
      45,    46,    47,    48,    15,    16,    17,    18,    19,    -1,
      21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,    -1,    -1,    -1,    45,    46,    47,    48,    15,    16,
      17,    18,    19,    -1,    21,    -1,    -1,    -1,    25,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    21,    -1,    45,    46,
      47,    48,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,     6,     7,    -1,    -1,    -1,
      45,    46,    47,    48,    15,    16,    17,    18,    19,    -1,
      21,     4,     5,     6,     7,    -1,     4,     5,     6,     7,
      -1,    -1,    15,    16,    17,    18,    19,    15,    16,    17,
      18,    19,    -1,    -1,    45,    46,    47,    48,    -1,    -1,
       4,    -1,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    20,    45,    46,    47,
      48,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      34,    -1,    36,    -1,    -1,    39,    -1,    41,     4,    43,
      44,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,    20,    -1,    -1,     8,    -1,    10,
      -1,    27,    -1,    -1,    30,    31,    32,    33,    34,    20,
      36,    -1,    -1,    39,    -1,    41,    27,    43,    44,    30,
      31,    32,    33,    34,    22,    36,    -1,    -1,    39,    -1,
      41,    29,    43,    44,    -1,    -1,    -1,    35,    -1,    -1,
      38,    -1,    -1,    -1,    42
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    23,    50,    51,    52,    53,    42,     0,    52,    10,
      26,    11,    41,    54,    55,    56,    58,    42,    13,    54,
       8,    12,    60,    10,    54,     9,    58,    61,    62,    22,
      29,    35,    38,    42,    57,    59,    12,    54,    12,     9,
      14,     3,    57,    57,    61,     4,     8,    10,    20,    27,
      30,    31,    32,    33,    34,    36,    39,    43,    44,    58,
      63,    65,    66,    67,    68,    69,    70,    72,    73,    63,
      65,     9,    65,    64,    65,    65,    65,    58,    59,    65,
      65,     3,     8,     4,     5,     6,     7,    15,    16,    17,
      18,    19,    21,    45,    46,    47,    48,     9,    11,    13,
      37,    12,    24,    65,     9,    65,    71,    65,    65,    65,
      65,    65,    58,    65,    65,    65,    65,    65,    65,    65,
      65,    64,    65,    57,    65,     9,    14,     8,    25,     3,
      28,    71,    71,    65,    65,    65,    28,    65
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    49,    50,    51,    52,    52,    53,    53,    54,    54,
      54,    55,    55,    56,    57,    57,    57,    57,    57,    58,
      59,    60,    60,    61,    61,    62,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    70,    70,    71,    71,    71,    72,    72,
      72,    73,    73
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     0,     2,     4,     6,     1,     3,
       2,     3,     5,     5,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     3,     3,     2,     2,     3,     1,
       1,     1,     3,     3,     5,     2,     1,     1,     1,     2,
       3,     1,     1,     1,     4,     6,     4,     6,     8,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     1,     2,     3,     1,     1,
       1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"<-\"", "\"-\"",
  "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\":\"",
  "\";\"", "\",\"", "\"^\"", "\".\"", "\"=\"", "\"<\"", "\"<=\"", "\"if\"",
  "\"and\"", "\"bool\"", "\"class\"", "\"do\"", "\"else\"", "\"extends\"",
  "\"false\"", "\"in\"", "\"int32\"", "\"isnull\"", "\"let\"", "\"new\"",
  "\"not\"", "\"self\"", "\"string\"", "\"true\"", "\"then\"", "\"unit\"",
  "\"while\"", "\"start\"", "\"object-identifier\"", "\"type-identifier\"",
  "\"integer-literal\"", "\"string-literal\"", "\"or\"", "\"!=\"", "\">\"",
  "\">=\"", "$accept", "start", "program", "program-aux", "class",
  "class-body", "field", "method", "type", "object-id", "type-id",
  "formals", "formals-aux", "formal", "block", "block-aux", "expr", "if",
  "while", "let", "bin-op", "un-op", "args", "literal", "boolean-literal", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   151,   151,   155,   158,   159,   162,   164,   167,   168,
     170,   173,   175,   180,   183,   184,   186,   188,   190,   193,
     199,   204,   205,   207,   209,   212,   215,   218,   220,   223,
     225,   227,   229,   231,   233,   235,   237,   239,   241,   243,
     245,   247,   249,   251,   254,   256,   259,   263,   265,   268,
     270,   272,   274,   276,   278,   280,   282,   284,   286,   288,
     290,   292,   295,   297,   299,   302,   303,   305,   308,   310,
     312,   313,   315
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 19 "vsop.y"
} // VSOP
#line 1690 "parser.cpp"

#line 318 "vsop.y"

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
