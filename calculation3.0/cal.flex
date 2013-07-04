%{
  #include "caltype.h"
  #include "exprtree.h"
  
  #define ASSIGN 258
  #define DOUBLE_CONST 259
  #define IDENTIFIER 260
  #define IF 261
  #define THEN 262
  #define ELSE 263
  #define FI 264
  #define WHILE 265
  #define LOOP 266
  #define POOL 267  
  
  typedef union YYSTYPE
  {
    Expression* expression;
	char		name[32];
	double 		num;
  }YYSTYPE;

  extern YYSTYPE yylval;
%}

%option noyywrap

DIGIT    [0-9]+
NOTATION \;|\{|\}|\(|\)|\+|\-|\*|\/|<|=
ASSIGN	 <-
BLANK    \f|\r|\ |\t|\v
NEWLINE  \n
IF			 (?i:if)
ELSE		 (?i:else)
WHILE		 (?i:while)
THEN		 (?i:then)
FI			 (?i:fi)
LOOP		 (?i:loop)
POOL		 (?i:pool)
IDENTFIER    [a-zA-Z][a-zA-Z0-9_]*


%%
{DIGIT}   {/*ECHO;*/ /*yylval.expression.m_data.name[0]=0;*/
		  yylval.num = atof(yytext);
		  return DOUBLE_CONST;}
{NOTATION} { /*ECHO*/; return yytext[0];}
{BLANK} { /*ECHO*/; }
{NEWLINE} { /*ECHO*/; }
{ASSIGN} {/*ECHO*/; return ASSIGN;}
{IF}	 {/*ECHO;*/ return IF;}
{ELSE}	 {/*ECHO;*/ return ELSE;}
{WHILE}  {/*ECHO;*/ return WHILE;}
{THEN}   {/*ECHO;*/ return THEN;}
{FI}   {/*ECHO;*/ return FI;}
{LOOP}   {/*ECHO;*/ return LOOP;}
{POOL}   {/*ECHO;*/ return POOL;}

{IDENTFIER} {/*ECHO*/; strcpy(yylval.name, yytext);
			return IDENTIFIER; }
.

%%

/*int main()
{
   yyin = fopen("text", "r");
   yylex();
}*/
