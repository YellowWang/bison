%{
  //#define YYSTYPE double
  #include <ctype.h>
  #include <stdio.h>
  int yylex (void);
  void yyerror (char const *);
%}

%token NUM
%left '+' '-'

%%
input:
/* empty */
| input line
;
line:
'\n'
| expr '\n' { printf ("%d\n", $1); }
;
expr:
NUM { $$ = $1; }
| expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
;
%%

int yylex (void)
{
  int c;
  /* Skip white space. */
  while ((c = getchar ()) == ' ' || c == '\t')
    continue;
  /* Process numbers. */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      scanf ("%d", &yylval);
      return NUM;
    }
  /* Return end-of-input. */
  if (c == EOF)
    return 0;
  /* Return a single char. */
  return c;
}
/* Called by yyparse on error. */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main (void)
{
  return yyparse ();
} 
