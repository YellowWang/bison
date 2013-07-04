#makefile

OBJ = lex.yy.o calculation3.0.tab.o symtab.o exprtree.o
CC = g++
INCLUDE = -I.
DEBUGDIR = ./debug
DIROBJ = $(addprefix $(DEBUGDIR)/, $(OBJ))
CCARG = -g

.PHONY : clean


cal :
	flex cal.flex
	bison calculation3.0.y
	$(CC) -c $(CCARG) symtab.c
	$(CC) -c $(CCARG) exprtree.cpp
	$(CC) -c $(CCARG) lex.yy.c
	$(CC) -c $(CCARG) calculation3.0.tab.c
	$(CC) -o cal $(CCARG) $(OBJ)



clean :
	rm cal $(OBJ)
