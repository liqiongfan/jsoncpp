#include <cstdlib>
#include <iostream>
#include "json_language.hh"

/*!header:re2c:on*/
#include "json_type.hpp"

struct scanner{
    char *start = nullptr;
    char *limit = nullptr;
    char *marker = nullptr;
    char *ctxmarker = nullptr;
    int   state = 0;
    json  result;
    int   line = 1;
    int   column = 0;
    std::string msg{};
    int   subline = 1;
    int   subcolumn = 0;

    scanner(const std::string &buffer) {
        this->start = (char *)buffer.data();
        this->limit = this->start + buffer.size();
        this->marker = nullptr;
        this->ctxmarker = nullptr;
        this->line = 1;
        this->column = 0;
        this->state = 0; /* for JSON mode */
    }
};
/*!header:re2c:off*/

#define YYCURSOR  l.start
#define YYLIMIT   l.limit
#define YYMARKER  l.marker
#define YYCTXMARKER l.ctxmarker
#define YYCTYPE unsigned char
#define YYGETCONDITION() l.state
#define YYSETCONDITION(cond) l.state=(yyc##cond)
#define GOTO(cond) goto yyc_##cond
#define SETANDJUMPTO(cond) YYSETCONDITION(cond); GOTO(cond)
#define FORWARD(lines, columns) l.line += (lines); l.column += (columns)
#define LOCATION yy::parser::location_type(nullptr, yy::location::counter_type(l.line), yy::location::counter_type(l.column))

yy::parser::symbol_type kk_lex(scanner &l) {

std:
    std::string data;
    char *begin = l.start;
skip:

/*!re2c
re2c:indent:top = 1;
re2c:yyfill:enable = 0;

DIGIT   = [0-9];
DIGITNZ = [1-9];
UINT    = "0" | (DIGITNZ DIGIT*);
INT     = ("-"|"+")? UINT ;
FLOAT   = (INT) ? "." DIGIT* ;
EXP     = ( INT | FLOAT ) [eE] [+-]? DIGIT+ ;
NL      = "\r"? "\n";
HEX     = "0"[xX][a-fA-F]+;
WS      = [ \t\r]+;
EOI     = "\000";
LABEL	= [a-zA-Z_\x80-\xff][a-zA-Z0-9_\x80-\xff]*;

<JSON>"{" { FORWARD(0, l.start - begin); return yy::parser::symbol_type('{', LOCATION); }
<JSON>"}" { FORWARD(0, l.start - begin); return yy::parser::symbol_type('}', LOCATION); }
<JSON>"[" { FORWARD(0, l.start - begin); return yy::parser::symbol_type('[', LOCATION); }
<JSON>"]" { FORWARD(0, l.start - begin); return yy::parser::symbol_type(']', LOCATION); }
<JSON>"," { FORWARD(0, l.start - begin); return yy::parser::symbol_type(',', LOCATION); }
<JSON>":" { FORWARD(0, l.start - begin); return yy::parser::symbol_type(':', LOCATION); }

<JSON>'NaN'        { FORWARD(0, l.start - begin); return yy::parser::make_NANN(json::nan(), LOCATION);                  }
<JSON>'null'       { FORWARD(0, l.start - begin); return yy::parser::make_NUL(json::null(), LOCATION);                  }
<JSON>'-inf'       { FORWARD(0, l.start - begin); return yy::parser::make_INF(json::infinity(true), LOCATION);          }
<JSON>("+")?'inf'  { FORWARD(0, l.start - begin); return yy::parser::make_INF(json::infinity(false), LOCATION);         }
<JSON>'-Infinity'       { FORWARD(0, l.start - begin); return yy::parser::make_INF(json::infinity(true), LOCATION);     }
<JSON>("+")?'Infinity'  { FORWARD(0, l.start - begin); return yy::parser::make_INF(json::infinity(false), LOCATION);    }
<JSON>'true'       { FORWARD(0, l.start - begin); return yy::parser::make_BOOLEAN(json::boolean(true), LOCATION);       }
<JSON>'false'      { FORWARD(0, l.start - begin); return yy::parser::make_BOOLEAN(json::boolean(false), LOCATION);      }

<JSON>NL {
    FORWARD(1, 0);
    l.column = 0; 
    goto std;
}

<JSON>WS { 
    FORWARD(0, l.start - begin); 
    goto std; 
}
<JSON>EOI {
    return yy::parser::make_YYEOF(LOCATION);
}

<JSON>LABEL {
    FORWARD(0, l.start - begin);
    std::string v(begin, l.start);
    return yy::parser::make_LABEL(v, LOCATION);
}

<JSON>["] {
    begin = l.start;
    l.subline = l.line;
    l.subcolumn = l.subcolumn;
    SETANDJUMPTO(KEY);
}

<KEY> EOI {
    l.msg = "double-quotation-marks string unclosed";
    l.line = l.subline;
    l.column = l.subcolumn;
    goto syntax_error;
}

<KEY>[\n] {
    if (*(l.start-2) == '\r') {
        if (*(l.start-3) != '\\') {
            goto syntax_error;
        }
        data = data.append(begin, l.start-3);
    } else {
        if (*(l.start-2) != '\\') {
            goto syntax_error;
        }
        data = data.append(begin, l.start-2);
    }
    begin = l.start;
    FORWARD(1, 0);
    l.column = 0; 
    SETANDJUMPTO(KEY);
}

<KEY>[ \f\t] {
    FORWARD(0, 1);
    data = data.append(begin, l.start);
    begin=l.start;
    SETANDJUMPTO(KEY);
}

<KEY>[^"] {
    FORWARD(0, 1);
    SETANDJUMPTO(KEY);
}

<KEY>["] {
    std::string v(begin, l.start-1);
    if (data.size() >= 1) {
        v = data + v;
    }
    data.clear();
    YYSETCONDITION(JSON);
    return yy::parser::make_STRING(v, LOCATION);
}

<JSON>['] {
    begin = l.start;
    l.subline = l.line;
    l.subcolumn = l.subcolumn;
    SETANDJUMPTO(KEY1);
}

<KEY1> EOI {
    l.msg = "single-quotation-marks string unclosed";
    l.line = l.subline;
    l.column = l.subcolumn;
    goto syntax_error;
}

<KEY1>[\n] {
    if (*(l.start-2) == '\r') {
        if (*(l.start-3) != '\\') {
            goto syntax_error;
        }
        data = data.append(begin, l.start-3);
    } else {
        if (*(l.start-2) != '\\') {
            goto syntax_error;
        }
        data = data.append(begin, l.start-2);
    }
    begin = l.start;
    FORWARD(1, 0);
    l.column = 0; 
    SETANDJUMPTO(KEY1);
}

<KEY1>[ \f\t] {
    FORWARD(0, 1);
    data = data.append(begin, l.start);
    begin=l.start;
    SETANDJUMPTO(KEY1);
}

<KEY1>[^'] {
    FORWARD(0, 1);
    SETANDJUMPTO(KEY1);
}

<KEY1>['] {
    std::string v(begin, l.start-1);
    if (data.size() >= 1) {
        v = data + v;
    }
    data.clear();
    YYSETCONDITION(JSON);
    return yy::parser::make_STRING(v, LOCATION);
}

<JSON>"//" {
    SETANDJUMPTO(COMMENTS);
}
<JSON>"#" {
    SETANDJUMPTO(COMMENTS);
}
<JSON>"/*" {
    l.subline = l.line;
    l.subcolumn = l.column;
    SETANDJUMPTO(COMMENT_STR1);
}
<COMMENTS>[^\n] {
    SETANDJUMPTO(COMMENTS);
}
<COMMENTS> EOI {
    l.msg = "single-line comments unclosed";
    l.line = l.subline;
    l.column = l.subcolumn;
    goto syntax_error;
}
<COMMENTS>[\n] {
    FORWARD(1, 0);
    l.column = 0;
    SETANDJUMPTO(JSON);
}
<COMMENT_STR1> [\n] {
    FORWARD(1, 0);
    l.column = 0;
    SETANDJUMPTO(COMMENT_STR1);
}
<COMMENT_STR1> "*/" {
    begin = l.start;
    SETANDJUMPTO(JSON);
}
<COMMENT_STR1> EOI {
    l.msg = "multiline comments unclosed";
    l.line = l.subline;
    l.column = l.subcolumn;
    goto syntax_error;
}
<COMMENT_STR1> [^] {
    SETANDJUMPTO(COMMENT_STR1);
}

<JSON>INT {
    FORWARD(0, l.start - begin);
    std::string str(begin, l.start);
    long ll = std::strtol(str.data(), nullptr, 10);
    return yy::parser::make_INT(ll, LOCATION);
}

<JSON>HEX {
    FORWARD(0, l.start - begin);
    std::string str(begin, l.start);
    long ll = std::strtol(str.data(), nullptr, 16);
    return yy::parser::make_HEX(json::hex(ll, str), LOCATION);
}

<JSON>FLOAT|EXP {
    FORWARD(0, l.start - begin);
    std::string str(begin, l.start);
    double d = std::strtod(str.data(), nullptr);
    return yy::parser::make_DOUBLE(d, LOCATION);
}
*/

syntax_error:
return yy::parser::make_YYerror(LOCATION);
}