%require "3.5"
%language "c++"

%defines
%define api.value.type variant
%define api.token.constructor
%define parse.trace
%define parse.error verbose
%define parse.lac full
%param {scanner &l}
%locations

%code requires {
    #include <vector>
    #include <string>
    #include "json_scanner.hh"
}

%code provides {
    json fromJson(const std::string &str);
}

%code {

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

    if (this->is_nan()) {
        return "NaN";
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
    std::string buf;
    std::string::size_type pos;
    if (l.limit== l.start - 1) {
        buf = msg;
        pos = std::string::npos;
    } else {
        buf = std::string(l.start, (l.limit-l.start > 300) ? l.start+300 : l.limit);
        pos = buf.find_first_of('\n', 0);
    }
    if (pos == std::string::npos) {
        message += buf;
    } else {
        message += buf.substr(0, pos);
    }
    throw message;
}

}}

%type<json>          value
%type<json::array>   array
%type<json::object>  object
%type<json::object>  pairs
%type<std::string>   key
%type<json::array>   elements

%token<long> INT "integer"
%token<json::hex> HEX "hex"
%token<json::boolean> BOOLEAN "boolean"
%token<json::null> NUL "null"
%token<json::infinity> INF "infinity"
%token<double> DOUBLE "double"
%token<std::string> STRING "string"
%token<std::string> LABEL "idetifier"
%token<json::nan> NANN "nan"

%token YYEOF 0
%token YYerror

%%

json: value YYEOF { l.result = $1; YYACCEPT; }
;

array:
 '[' elements array_end { $$ = $2; }
;

array_end:
  ']'
| ',' ']'
;


elements:
 value                  { $$.push_back($1);         }
| elements ',' value    { $1.push_back($3); $$=$1;  }
;

object:
  '{' pairs object_end   { $$ = $2; }
;

object_end:
  '}'
| ',' '}'
;

pairs:
  key ':' value         { $$.insert({$1, $3});          }
| pairs ',' key ':' value   { $1.insert({$3, $5}); $$ = $1; }
;


key:
  STRING   { $$ = $1; }
| LABEL    { $$ = $1; }
;

value:
  INT       { $$ = $1; }
| HEX       { $$ = $1; }  
| BOOLEAN   { $$ = $1; }
| NUL       { $$ = $1; }
| INF       { $$ = $1; }
| DOUBLE    { $$ = $1; }
| STRING    { $$ = $1; }
| array     { $$ = $1; }
| object    { $$ = $1; }
| NANN      { $$ = $1; }
| YYerror   {
    error(@1, l.msg);
}
;

%%