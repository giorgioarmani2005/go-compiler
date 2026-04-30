%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <optional>
#include <vector>
#include <string>
#include <map>

extern int yylex();
extern int yyparse();

void parsing_failure();

extern FILE* yyin;
extern FILE* yyout;

int last_label = 0;
int last_for_label = 0;
int last_if_label = 0;

typedef struct {
    int last_id = -1;
    std::map<std::string, int> variables;
} Scope;

std::vector<Scope> scopes;

int variable_lookup(const std::string& name);
int create_variable(const std::string& name);

void yyerror(const char* s);

void write_operation(int addr_dest) {
    fprintf(yyout, "WRITE [%d], ax\n", addr_dest);
}

void load_operation(int addr_src) {
    fprintf(yyout, "LOAD ax, [%d]\n", addr_src);
}

void push_num_operation(int num) {
    fprintf(yyout, "PUSH %d\n", num);
}

void push_reg_operation() {
    fprintf(yyout, "PUSH ax\n");
}

void pop_operation() {
    fprintf(yyout, "POP ax\n");
}

void sum_operation() {
    fprintf(yyout, "SUM\n");
}

void sub_operation() {
    fprintf(yyout, "SUB\n");
}

void mul_operation() {
    fprintf(yyout, "MUL\n");
}

void div_operation() {
    fprintf(yyout, "DIV\n");
}

void mod_operation() {
    fprintf(yyout, "MOD\n");
}

void or_operation() {
    fprintf(yyout, "OR\n");
}

void xor_operation() {
    fprintf(yyout, "XOR\n");
}

void and_operation() {
    fprintf(yyout, "AND\n");
}

void lshift_operation() {
    fprintf(yyout, "LSHIFT\n");
}

void rshift_operation() {
    fprintf(yyout, "RSHIFT\n");
}

void logical_or_operation() {
    fprintf(yyout, "LOR\n");
}

void logical_and_operation() {
    fprintf(yyout, "LAND\n");
}

void equal_operation() {
    fprintf(yyout, "EQ\n");
}

void not_equal_operation() {
    fprintf(yyout, "NEQ\n");
}

void lower_operation() {
    fprintf(yyout, "LW\n");
}

void greater_operation() {
    fprintf(yyout, "GT\n");
}

void lower_or_equal_operation() {
    fprintf(yyout, "LWEQ\n");
}

void greater_or_equal_operation() {
    fprintf(yyout, "GTEQ\n");
}

void and_not_operation() {
    fprintf(yyout, "ANDNOT\n");
}

void print_operation() {
    fprintf(yyout, "PRINT ax\n");
}

void label_operation(int label_num) {
    fprintf(yyout, "\n%d:\n", label_num);
}



%}

%union {
    int element_count;
    int val;
    char *str;

    // struct array_id {
    //     int current_array_id;
    //     int *variable_ids_array;
    // };
}

%token INT UINT INT8 INT16 INT32 INT64 UINT8 UINT16 UINT32 UINT64

%token NL
%token PACKAGE FUNC VAR SEMICOLON IF ELSE FOR BREAK CONTINUE RETURN
%token EQ NE LE GE
%token LAND LOR
%token ANDNOT LSHIFT RSHIFT
%token PLUSEQ MINUSEQ STAREQ DIVEQ MODEQ
%token ANDEQ OREQ XOREQ LSHIFTEQ RSHIFTEQ ANDNOTEQ
%token DEFINE
%token INC DEC
%token PRINT

%token <val> NUMBER
%token <str> NAME

%type <val> for_token
%type <val> if_token
%type <val> else_if_token
%type <val> else_token

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
    : NAME '=' expression {
        int variable_addr = create_variable($1);
        
        pop_operation();
        write_operation(variable_addr);
    }
    | NAME type '=' expression {
        int variable_addr = create_variable($1);
        
        pop_operation();
        write_operation(variable_addr);
    }
    | NAME ',' var_spec ',' expression {
        int variable_addr = create_variable($1);
        
        pop_operation();
        write_operation(variable_addr);
    }
    ;

short_var_decl
    : NAME DEFINE expression {
        int variable_addr = create_variable($1);

        pop_operation();
        write_operation(variable_addr);
    }
    | NAME ',' short_var_decl ',' expression {
        int variable_addr = create_variable($1);

        pop_operation();
        write_operation(variable_addr);
    }
    ;    



type
    : INT
    ;

statement_list
    : statement
    | statement_list SEMICOLON statement
    ;

statement
    : %empty
    | var_decl
    | assignment
    | inc_dec_stmt
    | if_stmt
    | for_stmt
    | block
    | short_var_decl
    | print_stmt
    ;

block
    : open_bracket statement_list close_bracket
    ;
open_bracket
    : '{'       { scopes.push_back({}); printf("Entered scope\n"); }
    ;
close_bracket
    : '}'       { scopes.pop_back(); printf("Left scope\n"); }
    ;

loop_statement_list
    : loop_statement
    | loop_statement_list SEMICOLON loop_statement
    ;

loop_statement
    : %empty
    | var_decl
    | assignment
    | inc_dec_stmt
    | for_stmt
    | block
    | break_stmt
    | continue_stmt
    | if_stmt_loop
    | print_stmt
    ;

loop_block
    : '{' loop_statement_list '}'
    ;

continue_stmt
    : CONTINUE
    ;

break_stmt
    : BREAK
    ;

expression
    : additive_expr
    ;
additive_expr
    : multiplicative_expr
    | additive_expr '+' multiplicative_expr {
        sum_operation();
    }
    | additive_expr '-' multiplicative_expr {
        sub_operation();
    }
    | additive_expr '|' multiplicative_expr {
        or_operation();
    }
    | additive_expr '^' multiplicative_expr {
        xor_operation();
    }
    ;
multiplicative_expr
    : unary_expr
    | multiplicative_expr '*' unary_expr {
        mul_operation();
    }
    | multiplicative_expr '/' unary_expr {
        div_operation();
    }
    | multiplicative_expr '%' unary_expr {
        mod_operation();
    }
    | multiplicative_expr LSHIFT unary_expr {
        lshift_operation();
    }
    | multiplicative_expr RSHIFT unary_expr {
        rshift_operation();
    }
    | multiplicative_expr '&' unary_expr {
        and_operation();
    }
    | multiplicative_expr ANDNOT unary_expr {
        and_not_operation();
    }
    ;
unary_expr
    : primary_expr
    | '+' unary_expr
    | '-' unary_expr {
        pop_operation();
        push_num_operation(0);
        push_reg_operation();
        sub_operation();
    }
    | '^' unary_expr {
        push_num_operation(0xFFFFFFFF);
        xor_operation();
    }
    ;

primary_expr
    : operand
    ;
operand
    : NAME {
        int variable_addr = variable_lookup($1);
        load_operation(variable_addr);
        push_reg_operation();
    }
    | NUMBER {
        push_num_operation($1);
    }
    | '(' expression ')'
    ;

logical_expression
    : logical_expression_and
    | logical_expression LOR logical_expression_and {
        logical_or_operation();
    }
    ;
logical_expression_and
    : logical_equality_expr
    | logical_expression_and LAND logical_equality_expr {
        logical_and_operation();
    }
    ;
logical_equality_expr
    : logical_relational_expr
    | logical_equality_expr EQ logical_relational_expr {
        equal_operation();
    }
    | logical_equality_expr NE logical_relational_expr {
        not_equal_operation();
    }
    ;
logical_relational_expr
    : logical_additive_expr
    | logical_relational_expr '<' logical_additive_expr {
        lower_operation();
    }
    | logical_relational_expr '>' logical_additive_expr {
        greater_operation();
    }
    | logical_relational_expr LE logical_additive_expr {
        lower_or_equal_operation();
    }
    | logical_relational_expr GE logical_additive_expr {
        greater_or_equal_operation();
    }
    ;
logical_additive_expr
    : logical_multiplicative_expr
    | logical_additive_expr '+' logical_multiplicative_expr {
        sum_operation();
    }
    | logical_additive_expr '-' logical_multiplicative_expr {
        sub_operation();
    }
    | logical_additive_expr '|' logical_multiplicative_expr {
        or_operation();
    }
    | logical_additive_expr '^' logical_multiplicative_expr {
        xor_operation();
    }
    ;
logical_multiplicative_expr
    : logical_unary_expr
    | logical_multiplicative_expr '*' logical_unary_expr {
        mul_operation();
    }
    | logical_multiplicative_expr '/' logical_unary_expr {
        div_operation();
    }
    | logical_multiplicative_expr '%' logical_unary_expr {
        mod_operation();
    }
    | logical_multiplicative_expr LSHIFT logical_unary_expr {
        lshift_operation();
    }
    | logical_multiplicative_expr RSHIFT logical_unary_expr {
        rshift_operation();
    }
    | logical_multiplicative_expr '&' logical_unary_expr {
        and_operation();
    }
    | logical_multiplicative_expr ANDNOT logical_unary_expr {
        and_not_operation();
    }
    ;

logical_unary_expr
    : logical_primary_expr
    | '!' logical_unary_expr {
        pop_operation();
        push_reg_operation();
        push_reg_operation();
        xor_operation();
    }
    | '+' logical_unary_expr
    | '-' logical_unary_expr {
        pop_operation();
        push_num_operation(0);
        push_reg_operation();
        sub_operation();
    }
    | '^' logical_unary_expr {
        push_num_operation(0xFFFFFFFF);
        xor_operation();
    }
    ;

logical_primary_expr
    : logical_operand
    ;

logical_operand
    : NAME {
        int variable_addr = variable_lookup($1);
        load_operation(variable_addr);
        push_reg_operation();
    }
    | NUMBER {
        push_num_operation($1);
    }
    | '(' expression ')'
    ;

variable_assignment
    : NAME '=' NAME {
        printf("%s = %s\n", $1, $3);
    }
    | NAME ',' variable_assignment ',' NAME {
        printf("%s = %s\n", $1, $5);
    }
    ;

assignment
    : variable_assignment
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
    : variable_assignment
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
    : NAME INC  { 
        int variable_addr = variable_lookup($1);

        load_operation(variable_addr);
        push_reg_operation();
        push_num_operation(1);
        sum_operation();
        write_operation(variable_addr);
    }
    | NAME DEC  {
        int variable_addr = variable_lookup($1);

        load_operation(variable_addr);
        push_reg_operation();
        push_num_operation(1);
        sum_operation();
        pop_operation();
        write_operation(variable_addr);
    }
    ;

if_token
    : IF {
        scopes.push_back({});
        printf("Entered scope\n");

        last_if_label = last_label + 1;
        last_label += 2;

        label_operation(last_if_label);

        $$ = last_if_label;
    }
    ;
else_if_token
    : ELSE IF {
        scopes.push_back({});
        printf("Entered scope\n");

        last_if_label = last_label + 1;
        last_label += 2;

        label_operation(last_if_label);

        $$ = last_if_label;
    }
    ;
else_token
    : ELSE {
        scopes.push_back({});
        printf("Entered scope\n");

        last_if_label = last_label + 1;
        last_label += 2;

        label_operation(last_if_label);

        $$ = last_if_label;
    }
    ;
if_stmt
    : if_token logical_expression block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
    | if_token logical_expression block elif_stmt {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;
    }
    | if_token short_var_decl SEMICOLON logical_expression block elif_stmt {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;
    }
    ;
elif_stmt
    : else_if_token logical_expression block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
    | else_if_token logical_expression block else_stmt {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;
    }
    | else_if_token logical_expression block elif_stmt {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;
    }
    | else_if_token short_var_decl SEMICOLON logical_expression block elif_stmt {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;
    }
    ;
else_stmt
    : else_token block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
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

for_token
    : FOR {
        scopes.push_back({});
        printf("Entered scope\n");

        last_for_label = last_label + 1;
        last_label += 2;

        label_operation(last_for_label);

        $$ = last_for_label;
    }
    ;
for_stmt
    : for_token loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
    | for_token logical_expression loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
    | for_token for_var_init SEMICOLON for_comparison SEMICOLON for_post loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation($1 + 1);
    }
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

print_stmt
    : PRINT '(' NAME ')' {
        int variable_addr = variable_lookup($3);

        load_operation(variable_addr);
        print_operation();
    }
    ;

%%

int variable_lookup(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->variables.find(name);
        if (found != it->variables.end()) {
            return found->second;
        }
    }
    
    parsing_failure();

    return -1;
}

int find_last_taken_id() {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->last_id != -1) return it->last_id;
    }

    return 0;
}

int create_variable(const std::string& name) {
    int new_id = find_last_taken_id() + 1;
    scopes.back().variables[name] = new_id;
    scopes.back().last_id = new_id;

    printf("New variable (%s) with id (%d) created\n", name.c_str(), new_id);

    return new_id;
}

void yyerror(const char* s) {
    fprintf(stderr, "Ошибка: %s\n", s);
}

void parsing_failure() {
    printf("Parsing failed in runtime\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: can't open file '%s'\n", argv[1]);
        return 1;
    }
    yyin = input_file;

    FILE* output_file = fopen(argv[2], "w");
    if (!input_file) {
        fprintf(stderr, "Error: cant't open file '%s'\n", argv[2]);
        return 1;
    }
    yyout = output_file;

    if (yyparse() == 0) {
        printf("Parsing completed successfully!\n");
    } else {
        printf("Parsing failed.\n");
    }

    fclose(input_file);
    return 0;
}