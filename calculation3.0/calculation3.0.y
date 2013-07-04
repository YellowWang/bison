%{
#define YYLTYPE int

#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "caltype.h"
#include "symtab.h"
#include "exprtree.h"
extern int yylex (void);
void yyerror (char const *);

%}

%union{
  Expressions* expressions;
  Expression* expression;
  char      name[32];
  double    num;
}

%token ASSIGN 258
%token<num> DOUBLE_CONST 259
%token<name> IDENTIFIER 260
%token IF 261 THEN 262 ELSE 263 FI 264
%token WHILE 265 LOOP 266 POOL 267
%right ASSIGN
%nonassoc '<'
%left '+' '-'
%left '*' '/'
%right NEG
%right '^'
%type<expression> expr
%type<expressions> exprs
%type<expressions> exprs_no

%%
input:
/* empty */
| exprs
;

exprs:
error { $$ = 0;}
| exprs error
| expr ';'
{
  $$ = t_single_exprs($1);
  Execute($1);
}
| exprs expr ';'
{
  $$ = t_append_exprs($1, $2);
  Execute($2);
}
;

expr:
IDENTIFIER { $$ = t_id($1); }
| DOUBLE_CONST { $$ = t_num($1);}
| expr '+' expr { $$ = t_plus($1, $3); }
| expr '-' expr { $$ = t_sub($1, $3); }
| expr '*' expr { $$ = t_mul($1, $3); }
| expr '/' expr { $$ = t_div($1, $3); }
| '(' expr ')' { $$ = $2;}
| '{' exprs_no '}' { $$ = t_block($2);}
| expr '<' expr { $$ = t_less($1, $3); }
| expr '=' expr { $$ = t_eq($1, $3); }
| IDENTIFIER ASSIGN expr { $$ = t_assign($1, $3); }
| IF expr THEN expr  ELSE expr FI { $$ = t_if($2, $4, $6); }
| WHILE expr LOOP expr POOL { $$ = t_while($2, $4); }
;

exprs_no:
expr ';'
{
  $$ = t_single_exprs($1);
}
| exprs_no expr ';'
{
  $$ = t_append_exprs($1, $2);
}
;
%%

/* Called by yyparse on error. */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main (void)
{
  return yyparse ();
} 
