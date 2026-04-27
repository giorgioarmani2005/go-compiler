%{
extern "C" {
    #include "grammar.tab.h"
}
#include <stdio.h>
#include <stdlib.h>

int asi_wrapper(int token);
int recv_wrapper();
static int insert_semicolon = 0;
static int prev_token = SEMICOLON;
%}

%option noyywrap
%option nounput
%option noinput

DIGIT    [0-9]
INTEGER  {DIGIT}+
EXPONENT [eE][+-]?{INTEGER}
NUMBER   {INTEGER}("."{INTEGER})?{EXPONENT}?|"."{INTEGER}{EXPONENT}?

%%

"//".*                      { /* игнорируем */ }
"/*"([^*]|\*+[^*/])*"*"+"/" { /* игнорируем */ }

[ \r\t]+                    { /* игнорируем */ }

\n                          { printf("NL\n"); return asi_wrapper(NL); }

"package"                   { printf("%s\n", yytext); return asi_wrapper(PACKAGE); }
"func"                      { printf("%s\n", yytext); return asi_wrapper(FUNC); }
"var"                       { printf("%s\n", yytext); return asi_wrapper(VAR); }
"const"                     { printf("%s\n", yytext); return asi_wrapper(CONST); }
"return"                    { printf("%s\n", yytext); return asi_wrapper(RETURN); }
"for"                       { printf("%s\n", yytext); return asi_wrapper(FOR); }
"break"                     { printf("%s\n", yytext); return asi_wrapper(BREAK); }
"if"                        { printf("%s\n", yytext); return asi_wrapper(IF); }
"else"                      { printf("%s\n", yytext); return asi_wrapper(ELSE); }

"++"                        { printf("%s\n", yytext); return asi_wrapper(INC); }
"--"                        { printf("%s\n", yytext); return asi_wrapper(DEC); }

"=="                        { printf("%s\n", yytext); return asi_wrapper(EQ); }
"!="                        { printf("%s\n", yytext); return asi_wrapper(NE); }
"<="                        { printf("%s\n", yytext); return asi_wrapper(LE); }
">="                        { printf("%s\n", yytext); return asi_wrapper(GE); }

"&&"                        { printf("%s\n", yytext); return asi_wrapper(LAND); }
"||"                        { printf("%s\n", yytext); return asi_wrapper(LOR); }

"&^"                        { printf("%s\n", yytext); return asi_wrapper(ANDNOT); }
"<<"                        { printf("%s\n", yytext); return asi_wrapper(LSHIFT); }
">>"                        { printf("%s\n", yytext); return asi_wrapper(RSHIFT); }
           
"+="                        { printf("%s\n", yytext); return asi_wrapper(PLUSEQ); }
"-="                        { printf("%s\n", yytext); return asi_wrapper(MINUSEQ); }
"*="                        { printf("%s\n", yytext); return asi_wrapper(STAREQ); }
"/="                        { printf("%s\n", yytext); return asi_wrapper(DIVEQ); }
"%="                        { printf("%s\n", yytext); return asi_wrapper(MODEQ); }
"&="                        { printf("%s\n", yytext); return asi_wrapper(ANDEQ); }
"|="                        { printf("%s\n", yytext); return asi_wrapper(OREQ); }
"^="                        { printf("%s\n", yytext); return asi_wrapper(XOREQ); }
"<<="                       { printf("%s\n", yytext); return asi_wrapper(LSHIFTEQ); }
">>="                       { printf("%s\n", yytext); return asi_wrapper(RSHIFTEQ); }
"&^="                       { printf("%s\n", yytext); return asi_wrapper(ANDNOTEQ); }

":="                        { printf("%s\n", yytext); return asi_wrapper(DEFINE); }
 
")"                         { printf("%s\n", yytext); return asi_wrapper(')'); }
"}"                         { printf("%s\n", yytext); return asi_wrapper('}'); }
"]"                         { printf("%s\n", yytext); return asi_wrapper(']'); }

;                           { printf("%s\n", yytext); return asi_wrapper(SEMICOLON); }



"int"                       { printf("%s\n", yytext); return asi_wrapper(INT); }



[a-zA-Z_][a-zA-Z0-9_]*      {
    printf("NAME: '%s'\n", yytext);
    yylval.str = strdup(yytext);
    return asi_wrapper(NAME);
}

{NUMBER}                    {
    printf("NUMBER: '%s'\n", yytext);
    yylval.dval = atof(yytext);
    return asi_wrapper(NUMBER);
}

.                           { printf("%s\n", yytext); return asi_wrapper(yytext[0]); }

%%

int asi_wrapper(int token) {
    if (token == NL) {
        if (insert_semicolon) {
            insert_semicolon = 0;
            printf("Insert semicolon\n");
            prev_token = SEMICOLON;
            return SEMICOLON;
        } else {
            printf("Tryna to skip NL\n");
            return asi_wrapper(yylex());
        }
    }

    insert_semicolon = 0;

    switch (token) {
        case INT:
        case NAME:
        case NUMBER:
        case RETURN:
        case BREAK:
        case CONTINUE:
        case ')':
        case '}':
        case INC:
        case DEC:
            insert_semicolon = 1;
            break;
    }

    prev_token = token;

    return token;
}