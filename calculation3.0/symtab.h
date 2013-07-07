#ifndef SYMTAB_H
#define SYMTAB_H

#include "caltype.h"  
#include <string.h>

extern EXPR_DATA g_symbols[100];
extern int g_symnum;

void SetValue(char* name, double num);
double GetValue(char* name);

#endif
