
#include "symtab.h"

EXPR_DATA g_symbols[100];
int g_symnum;

void SetValue(char* name, double num)
 {
   int i = 0;
   for (; i < g_symnum; i++)
   {
	 if (strcmp(g_symbols[i].name, name)==0)
	 {
	   g_symbols[i].num = num;
	   return;
	 }
   }
   if (i < 100)
   {
	 strcpy(g_symbols[i].name, name);
	 g_symbols[i].num = num;
	 i++;
	 g_symnum = i;
   }
 }
 double GetValue(char* name)
 {
   //printf("@GetV symnum=%d ", g_symnum);
   for (int i = 0; i < g_symnum; i++)
   {
	 if (strcmp(g_symbols[i].name, name)==0)
	 {
	   return g_symbols[i].num;
	 }
   }
   return 0;
 }

