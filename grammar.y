%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
void parsing_failure();
%}

%union {
    int element_count;
    double dval;
    char *str;
}

%token INT

%token NL
%token PACKAGE FUNC VAR CONST RETURN SEMICOLON IF ELSE FOR BREAK CONTINUE GOTO
%token EQ NE LE GE
%token LAND LOR
%token ANDNOT LSHIFT RSHIFT
%token PLUSEQ MINUSEQ STAREQ DIVEQ MODEQ
%token ANDEQ OREQ XOREQ LSHIFTEQ RSHIFTEQ ANDNOTEQ
%token DEFINE
%token INC DEC

%token <dval> NUMBER
%token <str> NAME

%type <element_count> identifier_list
%type <element_count> expression_list

%%

program: package_clause global_decls
package_clause: PACKAGE NAME SEMICOLON

global_decls
    : %empty
    | global_decl
    | global_decl SEMICOLON global_decls
    ;
global_decl
    : var_decl
    | const_decl
    | main_decl
    ;
main_decl
    : FUNC NAME '(' ')' block
    ;

var_decl
    : VAR var_spec
    | VAR '(' var_spec_list ')'
    ;
var_spec_list
    : var_spec
    | var_spec SEMICOLON
    | var_spec SEMICOLON var_spec_list
    ;
var_spec
    : identifier_list type
    | identifier_list type '=' expression_list  { if ($1 != $4) parsing_failure(); }
    | identifier_list '=' expression_list       { if ($1 != $3) parsing_failure(); }
    ;

short_var_decl
    : identifier_list DEFINE expression_list    { if ($1 != $3) parsing_failure(); }
    ;

const_decl
    : CONST const_spec_first
    | CONST '(' const_spec_list ')'
    ;
const_spec_list
    : const_spec_first
    | const_spec_first SEMICOLON
    | const_spec_list const_spec_rest SEMICOLON
    ;
const_spec_first
    : identifier_list type '=' expression_list  { if ($1 != $4) parsing_failure(); }
    | identifier_list '=' expression_list       { if ($1 != $3) parsing_failure(); }
    ;
const_spec_rest
    : identifier_list
    | identifier_list type '=' expression_list  { if ($1 != $4) parsing_failure(); }
    | identifier_list '=' expression_list       { if ($1 != $3) parsing_failure(); }
    ;

identifier_list
    : NAME                              { $$ = 1; }
    | NAME ',' identifier_list          { $$ = $3 + 1; }
    ;
expression_list
    : expression                        { $$ = 1; }
    | expression ',' expression_list    { $$ = $3 + 1; }
    ;

type
    : NAME
    | INT
    ;

statement_list
    : statement
    | statement_list SEMICOLON statement
    ;
statement
    : %empty
    | var_decl
    | const_decl
    | assignment
    | inc_dec_stmt
    | return_stmt
    | function_call
    | if_stmt
    | for_stmt
    | block
    | goto_stmt
    | labeled_stmt
    ;
block
    : '{' statement_list '}'
    ;

loop_statement_list
    : loop_statement
    | loop_statement_list SEMICOLON loop_statement
    ;
loop_statement
    : %empty
    | var_decl
    | const_decl
    | assignment
    | inc_dec_stmt
    | return_stmt
    | function_call
    | for_stmt
    | block
    | goto_stmt
    | labeled_stmt
    | break_stmt
    | continue_stmt
    | if_stmt_loop
    ;
loop_block
    : '{' loop_statement_list '}'
    ;


continue_stmt
    : CONTINUE
    | CONTINUE NAME
    ;

break_stmt
    : BREAK
    | BREAK NAME
    ;

goto_stmt
    : GOTO NAME
    ;

labeled_stmt
    : NAME ':' statement
    ;

return_stmt
    : RETURN
    | RETURN expression_list 
    ;

expression
    : logical_or_expr
    ;
logical_or_expr
    : logical_and_expr
    | logical_or_expr LOR logical_and_expr
    ;
logical_and_expr
    : equality_expr
    | logical_and_expr LAND equality_expr
    ;
equality_expr
    : relational_expr
    | equality_expr EQ relational_expr
    | equality_expr NE relational_expr
    ;
relational_expr
    : additive_expr
    | relational_expr '<' additive_expr
    | relational_expr '>' additive_expr
    | relational_expr LE additive_expr
    | relational_expr GE additive_expr
    ;
additive_expr
    : multiplicative_expr
    | additive_expr '+' multiplicative_expr
    | additive_expr '-' multiplicative_expr
    | additive_expr '|' multiplicative_expr
    | additive_expr '^' multiplicative_expr
    ;
multiplicative_expr
    : unary_expr
    | multiplicative_expr '*' unary_expr
    | multiplicative_expr '/' unary_expr
    | multiplicative_expr '%' unary_expr
    | multiplicative_expr LSHIFT unary_expr
    | multiplicative_expr RSHIFT unary_expr
    | multiplicative_expr '&' unary_expr
    | multiplicative_expr ANDNOT unary_expr
    ;
unary_expr
    : primary_expr
    | '!' unary_expr
    | '+' unary_expr
    | '-' unary_expr
    | '^' unary_expr
    | '*' unary_expr
    ;
primary_expr
    : operand
    | '&' NAME
    ;
operand
    : NAME
    | NUMBER
    | '(' expression ')'
    ;

logical_expression
    : logical_expression_and
    | logical_expression LOR logical_expression_and
    ;
logical_expression_and
    : logical_equality_expr
    | logical_expression_and LAND logical_equality_expr
    ;
logical_equality_expr
    : logical_relational_expr
    | logical_equality_expr EQ logical_relational_expr
    | logical_equality_expr NE logical_relational_expr
    ;
logical_relational_expr
    : logical_additive_expr
    | logical_relational_expr '<' logical_additive_expr
    | logical_relational_expr '>' logical_additive_expr
    | logical_relational_expr LE logical_additive_expr
    | logical_relational_expr GE logical_additive_expr
    ;
logical_additive_expr
    : logical_multiplicative_expr
    | logical_additive_expr '+' logical_multiplicative_expr
    | logical_additive_expr '-' logical_multiplicative_expr
    | logical_additive_expr '|' logical_multiplicative_expr
    | logical_additive_expr '^' logical_multiplicative_expr
    ;
logical_multiplicative_expr
    : logical_unary_expr
    | logical_multiplicative_expr '*' logical_unary_expr
    | logical_multiplicative_expr '/' logical_unary_expr
    | logical_multiplicative_expr '%' logical_unary_expr
    | logical_multiplicative_expr LSHIFT logical_unary_expr
    | logical_multiplicative_expr RSHIFT logical_unary_expr
    | logical_multiplicative_expr '&' logical_unary_expr
    | logical_multiplicative_expr ANDNOT logical_unary_expr
    ;
logical_unary_expr
    : logical_primary_expr
    | '!' logical_unary_expr
    | '+' logical_unary_expr
    | '-' logical_unary_expr
    | '^' logical_unary_expr
    ;
logical_primary_expr
    : logical_operand
    ;
logical_operand
    : NAME
    | NUMBER
    | '(' logical_expression ')'
    ;


assignment
    : identifier_list '=' expression_list       { if ($1 != $3) parsing_failure(); }
    | NAME PLUSEQ expression
    | NAME MINUSEQ expression
    | NAME STAREQ expression
    | NAME DIVEQ expression
    | NAME MODEQ expression
    | NAME ANDEQ expression
    | NAME OREQ expression
    | NAME XOREQ expression
    | NAME LSHIFTEQ expression
    | NAME RSHIFTEQ expression
    | NAME ANDNOTEQ expression
    ;
logical_assignment
    : NAME '=' logical_expression
    | NAME PLUSEQ logical_expression
    | NAME MINUSEQ logical_expression
    | NAME STAREQ logical_expression
    | NAME DIVEQ logical_expression
    | NAME MODEQ logical_expression
    | NAME ANDEQ logical_expression
    | NAME OREQ logical_expression
    | NAME XOREQ logical_expression
    | NAME LSHIFTEQ logical_expression
    | NAME RSHIFTEQ logical_expression
    | NAME ANDNOTEQ logical_expression
    ;

inc_dec_stmt
    : NAME INC
    | NAME DEC
    ;

function_call
    : NAME '(' ')'
    | NAME '(' expression_list ')'
    ;

if_stmt
    : IF logical_expression block elif_stmt
    | IF short_var_decl SEMICOLON logical_expression block elif_stmt
    ;
elif_stmt
    : else_stmt
    | ELSE IF logical_expression block elif_stmt
    | ELSE IF short_var_decl SEMICOLON logical_expression block elif_stmt
    ;
else_stmt
    : %empty
    | ELSE block
    ;

if_stmt_loop
    : IF logical_expression loop_block elif_stmt_loop
    | IF short_var_decl SEMICOLON logical_expression loop_block elif_stmt_loop
    ;
elif_stmt_loop
    : else_stmt_loop
    | ELSE IF logical_expression loop_block elif_stmt_loop
    | ELSE IF short_var_decl SEMICOLON logical_expression loop_block elif_stmt_loop
    ;
else_stmt_loop
    : %empty
    | ELSE loop_block
    ;

for_stmt
    : FOR loop_block
    | FOR logical_expression loop_block
    | FOR for_var_init SEMICOLON for_comparison SEMICOLON for_post loop_block
    ;
for_var_init
    : %empty
    | short_var_decl
    ;
for_comparison
    : %empty
    | logical_expression
    ;
for_post
    : %empty
    | logical_assignment
    | inc_dec_stmt
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Ошибка: %s\n", s);
}

void parsing_failure() {
    printf("Parsing failed.\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <unput_file>\n", argv[0]);
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: don't open file '%s'\n", argv[1]);
        return 1;
    }

    yyin = input_file;
    if (yyparse()==0) {
        printf("Parsing completed successfully!\n");
    } else {
        printf("Parsing failed.\n");
    }

    fclose(input_file);
    return 0;
}