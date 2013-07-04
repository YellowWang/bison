#ifndef EXPRTREE_H
#define EXPRTREE_H

class Expression;
class Expressions;
class Expr_plus;
class Expr_assign;
class Expr_num;

void Execute(Expression* e);
void Execute(Expressions* exprs);

Expression* t_id(char* name);
Expression* t_num(double num);
Expression* t_assign(char* name, Expression* e);
Expression* t_plus(Expression* e1, Expression* e2);
Expression* t_sub(Expression* e1, Expression* e2);
Expression* t_mul(Expression* e1, Expression* e2);
Expression* t_div(Expression* e1, Expression* e2);
Expression* t_if(Expression* con, Expression* et, Expression* ef);
Expression* t_less(Expression* e1, Expression* e2);
Expression* t_eq(Expression* e1, Expression* e2);
Expression* t_while(Expression* con, Expression* expr);
Expression* t_block(Expressions* exprs);
Expressions* t_single_exprs(Expression* e);
Expressions* t_append_exprs(Expressions* exprs, Expression* e);
#endif
