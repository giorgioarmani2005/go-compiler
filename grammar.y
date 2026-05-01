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

typedef struct {
    int last_id = -1;
    std::map<std::string, int> variables;
} Scope;

std::vector<Scope> scopes;
std::vector<std::vector<int>> if_label_ids;
std::vector<int> for_label_ids;

int variable_lookup(const std::string& name);
int find_last_taken_id();
int create_variable(const std::string& name);

void yyerror(const char* s);

void write_reg_operation(int addr_dest) {
    fprintf(yyout, "WRITE [%d], ax\n", addr_dest);
}

void write_num_operation(int addr_dest, int num) {
    fprintf(yyout, "WRITE [%d], %d\n", addr_dest, num);
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
    fprintf(yyout, "CMP OR\n");
}

void logical_and_operation() {
    fprintf(yyout, "CMPLAND\n");
}

void and_not_operation() {
    fprintf(yyout, "CMP ANDNOT\n");
}

void equal_operation() {
    fprintf(yyout, "CMP EQ\n");
}

void not_equal_operation() {
    fprintf(yyout, "CMP NEQ\n");
}

void lower_operation() {
    fprintf(yyout, "CMP LW\n");
}

void greater_operation() {
    fprintf(yyout, "CMP GT\n");
}

void lower_or_equal_operation() {
    fprintf(yyout, "CMP LWEQ\n");
}

void greater_or_equal_operation() {
    fprintf(yyout, "CMP GTEQ\n");
}

void print_operation() {
    fprintf(yyout, "PRINT ax\n");
}

void label_operation(int label_num) {
    fprintf(yyout, "\n%d:\n", label_num);
}

void jmp_operation(int label_num) {
    fprintf(yyout, "JMP %d\n", label_num);
}

void halt_operation() {
    fprintf(yyout, "HALT\n");
}

void jmp_equal_operation(int label_num) {
    fprintf(yyout, "JMPEQ %d\n", label_num);
}

void process_unary(char *variable_name, void (*unary_operation)()) {
    int variable_id = variable_lookup(variable_name);

    load_operation(variable_id);
    push_reg_operation();
    unary_operation();
    pop_operation();
    write_reg_operation(variable_id);
}

%}

%union {
    int element_count;
    int val;
    char *str;
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

%type <val> identifier_list

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


func_token
    : FUNC { scopes.push_back({}); printf("Entered scope\n"); }
    ;
main_decl
    : func_token NAME '(' ')' block {
        scopes.pop_back(); printf("Left scope\n");
    }
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
    : identifier_list type {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - $1; i <= last_variable_id; ++i) {
            write_num_operation(i, 0);
        }
    }
    | identifier_list type '=' expression_list {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - $1; i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
    | identifier_list '=' expression_list {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - $1; i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
    ;

identifier_list
    : NAME {
        create_variable($1);
        
        $$ = 0;
    }
    | NAME ',' identifier_list {
        create_variable($1);

        $$ = $3 + 1;
    }
    ;
/* identifier_list_assignment
    : NAME {
        create_variable($1);
        
        $$ = 0;
    }
    | NAME ',' identifier_list {
        create_variable($1);

        $$ = $3 + 1;
    }
    ; */
expression_list
    : expression
    | expression ',' expression_list
    ;

short_var_decl
    : identifier_list DEFINE expression_list {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - $1; i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
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
    | short_var_decl
    | print_stmt
    | return_stmt
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
    | assignment
    | inc_dec_stmt
    | for_stmt
    | block
    | break_stmt
    | continue_stmt
    | return_stmt
    | if_stmt_loop
    | print_stmt
    ;

loop_block
    : '{' loop_statement_list '}'
    ;

continue_stmt
    : CONTINUE {
        jmp_operation(for_label_ids.back() + 2);
    }
    ;

break_stmt
    : BREAK {
        jmp_operation(for_label_ids.back() + 1);
    }
    ;

return_stmt
    : RETURN {
        halt_operation();
    }
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
    : logical_expression_or
    ;
logical_expression_or
    : logical_expression_and
    | logical_expression_or LOR logical_expression_and {
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

assignment
    : NAME '=' expression {
        int variable_id = variable_lookup($1);

        pop_operation();
        write_reg_operation(variable_id);
    }
    | NAME PLUSEQ expression {
        process_unary($1, sum_operation);
    }
    | NAME MINUSEQ expression {
        process_unary($1, sub_operation);
    }
    | NAME STAREQ expression {
        process_unary($1, mul_operation);
    }
    | NAME DIVEQ expression {
        process_unary($1, div_operation);
    }
    | NAME MODEQ expression {
        process_unary($1, mod_operation);
    }
    | NAME ANDEQ expression {
        process_unary($1, and_operation);
    }
    | NAME OREQ expression {
        process_unary($1, or_operation);
    }
    | NAME XOREQ expression {
        process_unary($1, xor_operation);
    }
    | NAME LSHIFTEQ expression {
        process_unary($1, lshift_operation);
    }
    | NAME RSHIFTEQ expression {
        process_unary($1, rshift_operation);
    }
    | NAME ANDNOTEQ expression
    ;

logical_assignment
    : NAME '=' expression {
        int variable_id = variable_lookup($1);

        pop_operation();
        write_reg_operation(variable_id);
    }
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
        pop_operation();
        write_reg_operation(variable_addr);
    }
    | NAME DEC  {
        int variable_addr = variable_lookup($1);

        load_operation(variable_addr);
        push_reg_operation();
        push_num_operation(1);
        sum_operation();
        pop_operation();
        write_reg_operation(variable_addr);
    }
    ;

if_token
    : IF {
        scopes.push_back({});
        printf("Entered scope\n");

        if_label_ids.push_back({last_label + 1});

        last_label += 2;
    }
    ;
else_if_token
    : ELSE IF {
        scopes.push_back({});
        printf("Entered scope\n");

        int new_id = if_label_ids.back().back() + 1;
        label_operation(new_id);
        if_label_ids.back().push_back(new_id);

        last_label += 1;
    }
    ;
else_token
    : ELSE {
        scopes.push_back({});
        printf("Entered scope\n");

        int new_id = if_label_ids.back().back() + 1;
        label_operation(new_id);
        if_label_ids.back().push_back(new_id);

        last_label += 1;
    }
    ;
if_stmt
    : if_token if_comparison block {
        scopes.pop_back();
        printf("Left if scope\n");

        label_operation(if_label_ids.back().back() + 1);
        label_operation(if_label_ids.back().front());

        if_label_ids.pop_back();
    }
    | if_token if_comparison if_block elif_stmt
    | if_token if_comparison if_block else_stmt
    | if_token short_var_decl SEMICOLON if_comparison if_block elif_stmt
    | if_token short_var_decl SEMICOLON if_comparison if_block else_stmt
    ;
elif_stmt
    : else_if_token if_comparison block {
        scopes.pop_back();
        printf("Left else if scope\n");

        last_label -= 1;

        label_operation(if_label_ids.back().back() + 1);
        label_operation(if_label_ids.back().front());

        if_label_ids.pop_back();
    }
    | else_if_token if_comparison if_block elif_stmt
    | else_if_token if_comparison if_block else_stmt
    | else_if_token short_var_decl SEMICOLON if_comparison if_block elif_stmt
    ;
else_stmt
    : else_token block {
        scopes.pop_back();
        printf("Left if scope\n");

        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
    ;

if_stmt_loop
    : if_token if_comparison loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation(if_label_ids.back().back() + 1);
        label_operation(if_label_ids.back().front());
        
        if_label_ids.pop_back();
    }
    | if_token if_comparison if_loop_block elif_stmt_loop
    | if_token if_comparison if_loop_block else_stmt_loop
    | if_token short_var_decl SEMICOLON if_comparison if_loop_block elif_stmt_loop
    | if_token short_var_decl SEMICOLON if_comparison if_loop_block else_stmt_loop
    ;
elif_stmt_loop
    : else_if_token if_comparison loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;

        label_operation(if_label_ids.back().back() + 1);
        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
    | else_if_token if_comparison if_loop_block elif_stmt_loop
    | else_if_token if_comparison if_loop_block else_stmt_loop
    | else_if_token short_var_decl SEMICOLON if_comparison if_loop_block elif_stmt_loop
    ;
else_stmt_loop
    : else_token loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
    ;
if_comparison
    : logical_expression {
        push_num_operation(0);
        equal_operation();
        jmp_equal_operation(if_label_ids.back().back() + 1);
    }
    ;
if_block
    : block {
        scopes.pop_back();
        printf("Left if scope\n");

        jmp_operation(if_label_ids.back().front());
    }
    ;
if_loop_block
    : loop_block {
        scopes.pop_back();
        printf("Left if scope\n");

        jmp_operation(if_label_ids.back().front());
    }
    ;

for_token
    : FOR {
        scopes.push_back({});
        printf("Entered scope\n");

        for_label_ids.push_back(last_label + 1);

        $$ = last_label + 1;
        last_label += 4;
    }
    ;
for_stmt
    : for_token loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation($1 + 2);
        label_operation($1 + 1);

        for_label_ids.pop_back();
    }
    | for_token logical_expression loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation($1 + 2);
        label_operation($1 + 1);

        for_label_ids.pop_back();
    }
    | for_token for_var_init SEMICOLON for_comparison SEMICOLON for_post loop_block {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation($1 + 2);
        label_operation($1 + 1);

        for_label_ids.pop_back();
    }
    ;
for_var_init
    : %empty {
        label_operation(for_label_ids.back());
    }
    | short_var_decl {
        label_operation(for_label_ids.back());
    }
    ;
for_comparison
    : %empty
    | logical_expression {
        push_num_operation(0);
        equal_operation();
        jmp_equal_operation(for_label_ids.back() + 1);
        jmp_operation(for_label_ids.back() + 3);
        label_operation(for_label_ids.back() + 2);
    }
    ;
for_post
    : %empty
    | logical_assignment {
        jmp_operation(for_label_ids.back());
        label_operation(for_label_ids.back() + 3);
    }
    | inc_dec_stmt {
        jmp_operation(for_label_ids.back());
        label_operation(for_label_ids.back() + 3);
    }
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