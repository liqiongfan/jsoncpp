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





#include "json_language.hh"


// Unqualified %code blocks.
#line 23 "json_language.yy"


yy::parser::symbol_type kk_lex(scanner &l);

template<>
json::json(std::initializer_list<json> t): ptr( new data<array>(t) ) { name = typeid(array).name(); }

template<>
json::json(bool t): ptr( new data<boolean>(t) ) { name = typeid(boolean).name(); }

std::string json::get_string() {
    if (this->is<const char *>()) {
        return std::string(this->get<const char *>());
    } else {
        return this->get<std::string>();
    }
}

std::string json::toString(bool hex) 
{
    if (this->is_array()) {
        std::string str = "[";
        auto v = this->get_array();
        for (auto i = 0; i < v.size(); i++) {
            str = str.append(v.at(i).toString(hex));
            if (i < v.size() - 1) {
                str = str.append(",");
            }
        }
        return str.append("]");
    }

    if (this->is_double()) {
        return std::to_string(this->get_double());
    }
    if (this->is_float()) {
        return std::to_string(this->get_float());
    }
    if (this->is_int()) {
        return std::to_string(this->get_int());
    }
    if (this->is_long()) {
        return std::to_string(this->get_long());
    }

    if (this->is_string()) {
        std::string p{};
        for (auto c : this->get_string()) {
            if (c == '"') {
                p = p.append(1, '\\');
            }
            p = p.append(1, c);
        }
        return std::string("\"").append(p).append("\"");
    }
    if (this->is_null()) {
        return "null";
    }

    if (this->is_infinity()) {
        if (this->get_infinity().neg) {
            return "-Infinity";
        } else {
            return "Infinity";
        }
    }

    if (this->is_hex()) {
        if (hex) {
            return this->get_hex().raw_value;
        } else {
            return std::to_string(this->get_hex().value);
        }
    }

    if (this->is_bool()) {
        if (this->get_bool().yes) {
            return "true";
        } else {
            return "false";
        }
    }

    if (this->is_object()) {
        auto i = 0;
        auto m = this->get_object();
        std::string str = "{";
        for (auto begin = m.begin(); begin != m.end(); begin++, i++) {
            str = str.append("\"").append(begin->first).append("\":");
            str = str.append(begin->second.toString(hex));
            if (i < m.size() -1) {
                str = str.append(",");
            }
        }
        return str.append("}");
    }

    return "";
}

json fromJson(const std::string &str)
{
    scanner l(str);

    yy::parser parse(l);
    parse();

    return l.result;
}

namespace yy {

auto yylex(scanner &l) -> parser::symbol_type {
    return kk_lex(l);
}

auto parser::error(const location_type& loc, const std::string &msg) -> void {
    auto message = "Unknown token appears in [line:column]:\n --> " + std::to_string(loc.end.line) + ":" + std::to_string(loc.end.column) + " | ";
    auto buf = std::string(l.start, (l.limit-l.start > 300) ? l.start+300 : l.limit);
    auto pos = buf.find_first_of('\n', 0);
    if (pos == std::string::npos) {
        message += buf;
    } else {
        message += buf.substr(0, pos);
    }
    throw message;
}

}

#line 177 "json_language.cc"


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

namespace yy {
#line 269 "json_language.cc"

  /// Build a parser object.
  parser::parser (scanner &l_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      l (l_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE: // "double"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_value: // value
        value.YY_MOVE_OR_COPY< json > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array: // array
      case symbol_kind::S_elements: // elements
        value.YY_MOVE_OR_COPY< json::array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.YY_MOVE_OR_COPY< json::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX: // "hex"
        value.YY_MOVE_OR_COPY< json::hex > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INF: // "infinity"
        value.YY_MOVE_OR_COPY< json::infinity > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUL: // "null"
        value.YY_MOVE_OR_COPY< json::null > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_object: // object
      case symbol_kind::S_pairs: // pairs
        value.YY_MOVE_OR_COPY< json::object > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "integer"
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_LABEL: // "label"
      case symbol_kind::S_key: // key
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

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE: // "double"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_value: // value
        value.move< json > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array: // array
      case symbol_kind::S_elements: // elements
        value.move< json::array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< json::boolean > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_HEX: // "hex"
        value.move< json::hex > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INF: // "infinity"
        value.move< json::infinity > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUL: // "null"
        value.move< json::null > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_object: // object
      case symbol_kind::S_pairs: // pairs
        value.move< json::object > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "integer"
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_LABEL: // "label"
      case symbol_kind::S_key: // key
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE: // "double"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_value: // value
        value.copy< json > (that.value);
        break;

      case symbol_kind::S_array: // array
      case symbol_kind::S_elements: // elements
        value.copy< json::array > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< json::boolean > (that.value);
        break;

      case symbol_kind::S_HEX: // "hex"
        value.copy< json::hex > (that.value);
        break;

      case symbol_kind::S_INF: // "infinity"
        value.copy< json::infinity > (that.value);
        break;

      case symbol_kind::S_NUL: // "null"
        value.copy< json::null > (that.value);
        break;

      case symbol_kind::S_object: // object
      case symbol_kind::S_pairs: // pairs
        value.copy< json::object > (that.value);
        break;

      case symbol_kind::S_INT: // "integer"
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_LABEL: // "label"
      case symbol_kind::S_key: // key
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE: // "double"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_value: // value
        value.move< json > (that.value);
        break;

      case symbol_kind::S_array: // array
      case symbol_kind::S_elements: // elements
        value.move< json::array > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< json::boolean > (that.value);
        break;

      case symbol_kind::S_HEX: // "hex"
        value.move< json::hex > (that.value);
        break;

      case symbol_kind::S_INF: // "infinity"
        value.move< json::infinity > (that.value);
        break;

      case symbol_kind::S_NUL: // "null"
        value.move< json::null > (that.value);
        break;

      case symbol_kind::S_object: // object
      case symbol_kind::S_pairs: // pairs
        value.move< json::object > (that.value);
        break;

      case symbol_kind::S_INT: // "integer"
        value.move< long > (that.value);
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_LABEL: // "label"
      case symbol_kind::S_key: // key
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
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
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

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

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
            symbol_type yylookahead (yylex (l));
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
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
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
      case symbol_kind::S_DOUBLE: // "double"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_value: // value
        yylhs.value.emplace< json > ();
        break;

      case symbol_kind::S_array: // array
      case symbol_kind::S_elements: // elements
        yylhs.value.emplace< json::array > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        yylhs.value.emplace< json::boolean > ();
        break;

      case symbol_kind::S_HEX: // "hex"
        yylhs.value.emplace< json::hex > ();
        break;

      case symbol_kind::S_INF: // "infinity"
        yylhs.value.emplace< json::infinity > ();
        break;

      case symbol_kind::S_NUL: // "null"
        yylhs.value.emplace< json::null > ();
        break;

      case symbol_kind::S_object: // object
      case symbol_kind::S_pairs: // pairs
        yylhs.value.emplace< json::object > ();
        break;

      case symbol_kind::S_INT: // "integer"
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_LABEL: // "label"
      case symbol_kind::S_key: // key
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
  case 2: // json: value $end
#line 171 "json_language.yy"
                  { l.result = yystack_[1].value.as < json > (); YYACCEPT; }
#line 894 "json_language.cc"
    break;

  case 3: // array: '[' elements array_end
#line 175 "json_language.yy"
                        { yylhs.value.as < json::array > () = yystack_[1].value.as < json::array > (); }
#line 900 "json_language.cc"
    break;

  case 6: // elements: value
#line 185 "json_language.yy"
                        { yylhs.value.as < json::array > ().push_back(yystack_[0].value.as < json > ());         }
#line 906 "json_language.cc"
    break;

  case 7: // elements: elements ',' value
#line 186 "json_language.yy"
                        { yystack_[2].value.as < json::array > ().push_back(yystack_[0].value.as < json > ()); yylhs.value.as < json::array > ()=yystack_[2].value.as < json::array > ();  }
#line 912 "json_language.cc"
    break;

  case 8: // object: '{' pairs object_end
#line 190 "json_language.yy"
                         { yylhs.value.as < json::object > () = yystack_[1].value.as < json::object > (); }
#line 918 "json_language.cc"
    break;

  case 11: // pairs: key ':' value
#line 199 "json_language.yy"
                        { yylhs.value.as < json::object > ().insert({yystack_[2].value.as < std::string > (), yystack_[0].value.as < json > ()});          }
#line 924 "json_language.cc"
    break;

  case 12: // pairs: pairs ',' key ':' value
#line 200 "json_language.yy"
                            { yystack_[4].value.as < json::object > ().insert({yystack_[2].value.as < std::string > (), yystack_[0].value.as < json > ()}); yylhs.value.as < json::object > () = yystack_[4].value.as < json::object > (); }
#line 930 "json_language.cc"
    break;

  case 13: // key: "string"
#line 205 "json_language.yy"
           { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 936 "json_language.cc"
    break;

  case 14: // key: "label"
#line 206 "json_language.yy"
           { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 942 "json_language.cc"
    break;

  case 15: // value: "integer"
#line 210 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < long > (); }
#line 948 "json_language.cc"
    break;

  case 16: // value: "hex"
#line 211 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::hex > (); }
#line 954 "json_language.cc"
    break;

  case 17: // value: "boolean"
#line 212 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::boolean > (); }
#line 960 "json_language.cc"
    break;

  case 18: // value: "null"
#line 213 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::null > (); }
#line 966 "json_language.cc"
    break;

  case 19: // value: "infinity"
#line 214 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::infinity > (); }
#line 972 "json_language.cc"
    break;

  case 20: // value: "double"
#line 215 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < double > (); }
#line 978 "json_language.cc"
    break;

  case 21: // value: "string"
#line 216 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < std::string > (); }
#line 984 "json_language.cc"
    break;

  case 22: // value: array
#line 217 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::array > (); }
#line 990 "json_language.cc"
    break;

  case 23: // value: object
#line 218 "json_language.yy"
            { yylhs.value.as < json > () = yystack_[0].value.as < json::object > (); }
#line 996 "json_language.cc"
    break;

  case 24: // value: error
#line 219 "json_language.yy"
            {
    error(yystack_[0].location, "Unknown token"); 
}
#line 1004 "json_language.cc"
    break;


#line 1008 "json_language.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
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
      yy_lac_discard_ ("error recovery");
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
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }


  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -10;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      24,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,    24,
      14,     2,   -10,   -10,    10,    27,   -10,   -10,   -10,     6,
      -3,   -10,   -10,   -10,     0,   -10,     7,   -10,   -10,    24,
     -10,   -10,   -10,    18,   -10,    24,   -10
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    24,    15,    16,    17,    18,    19,    20,    21,     0,
       0,     0,    22,    23,     0,     0,     6,    13,    14,     0,
       0,     1,     2,     4,     0,     3,     0,     9,     8,     0,
       5,     7,    10,     0,    11,     0,    12
  };

  const signed char
  parser::yypgoto_[] =
  {
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,    -8,    -9
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    11,    12,    25,    15,    13,    28,    19,    20,    14
  };

  const signed char
  parser::yytable_[] =
  {
      16,     1,    21,     2,     3,     4,     5,     6,     7,     8,
      22,     9,    30,    29,    10,    31,    17,    18,    33,    26,
      34,    27,    32,    17,    18,     1,    36,     2,     3,     4,
       5,     6,     7,     8,    35,     9,     0,     0,    10,    23,
      24
  };

  const signed char
  parser::yycheck_[] =
  {
       9,     1,     0,     3,     4,     5,     6,     7,     8,     9,
       0,    11,    12,    16,    14,    24,     9,    10,    26,    13,
      29,    15,    15,     9,    10,     1,    35,     3,     4,     5,
       6,     7,     8,     9,    16,    11,    -1,    -1,    14,    12,
      13
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,     7,     8,     9,    11,
      14,    18,    19,    22,    26,    21,    26,     9,    10,    24,
      25,     0,     0,    12,    13,    20,    13,    15,    23,    16,
      12,    26,    15,    25,    26,    16,    26
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    17,    18,    19,    20,    20,    21,    21,    22,    23,
      23,    24,    24,    25,    25,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     2,     1,     3,     3,     1,
       2,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"integer\"",
  "\"hex\"", "\"boolean\"", "\"null\"", "\"infinity\"", "\"double\"",
  "\"string\"", "\"label\"", "'['", "']'", "','", "'{'", "'}'", "':'",
  "$accept", "json", "array", "array_end", "elements", "object",
  "object_end", "pairs", "key", "value", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   171,   171,   175,   179,   180,   185,   186,   190,   194,
     195,   199,   200,   205,   206,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219
  };

  void
  parser::yy_stack_print_ () const
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
  parser::yy_reduce_print_ (int yyrule) const
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


} // yy
#line 1626 "json_language.cc"

#line 224 "json_language.yy"
