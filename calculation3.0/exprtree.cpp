
#include "exprtree.h"
#include "caltype.h"
#include "symtab.h"
#include <stdio.h>
#include <vector>

bool float_eq(double id, double num)
{
  double sub = id - num;
  if (sub < 0.00001f && sub > -0.00001f)
    return true;
  return false;
}
  

class Expression
{
public:
  Expression(){};
  virtual double execute()
  {
	return 0;
  };
};

class Expressions
{
public:
  Expressions(Expression* e)
  {
    push(e);
  }

  void push(Expression* e)
  {
    m_vExpr.push_back(e);
  }
  virtual double execute()
  {
    for (int i = 0; i < m_vExpr.size(); i++)
    {
	  if (m_vExpr[i])
		m_vExpr[i]->execute();
    }
    return 0;
  };

  std::vector<Expression*> m_vExpr;
};


class Expr_plus : public Expression
{
public:
  Expr_plus(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;
	double num1 = m_e1->execute();
	double num2 = m_e2->execute();
	return  num1 + num2;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_sub : public Expression
{
public:
  Expr_sub(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;
	double num1 = m_e1->execute();
	double num2 = m_e2->execute();
	return  num1 - num2;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_mul : public Expression
{
public:
  Expr_mul(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;
	double num1 = m_e1->execute();
	double num2 = m_e2->execute();
	return  num1 * num2;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_div : public Expression
{
public:
  Expr_div(Expression* e1, Expression* e2)
  {
	m_e1 = e1;
	m_e2 = e2;
  }
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;
	double num1 = m_e1->execute();
	double num2 = m_e2->execute();
	return  num1 / num2;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_assign : public Expression
{
public:
  Expr_assign(char* name, Expression* e)
  {
	m_name[0]=0;
	if (name)
	  strcpy(m_name, name);
	m_e = e;
  }
  virtual double execute()
  {
	if (m_name[0]==0 || !m_e)
	  return 0;
	
	double ace = m_e->execute();
	
	SetValue(m_name, ace);
	
	return ace;
  }

protected:
  char        m_name[32];
  Expression* m_e;
};

class Expr_num : public Expression
{
public:
  Expr_num(double num)
  {
	m_num = num;
  }
  virtual double execute()
  {
	return m_num;
  }

protected:
  double m_num;
};

class Expr_ID : public Expression
{
public:
  Expr_ID(char* name)
  {
	m_name[0]=0;
	if (name)
	  strcpy(m_name, name);
  }
  virtual double execute()
  {
	if (m_name[0]==0)
	  return 0;
	double num = 0;
	num = GetValue(m_name);
	SetValue(m_name, num);
	return num;
  }

protected:
  char m_name[32];
};

class Expr_if : public Expression
{
public:
  Expr_if(Expression* con, Expression* et, Expression* ef)
  {
	m_con = con;
	m_et = et;
	m_ef = ef;
  }
  
  virtual double execute()
  {
	if (!m_con || !m_ef || !m_et)
	  return 0;
	
	double b = m_con->execute();
	if (float_eq(b, 0))
	  m_ef->execute();
	else
	  m_et->execute();
	return 0;
  }

protected:
  Expression* m_con;
  Expression* m_et;
  Expression* m_ef;
};

class Expr_less : public Expression
{
public:
  Expr_less(Expression* e1, Expression* e2)
  {
    m_e1 = e1;
    m_e2 = e2;
  }
  
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;

    double num1 = m_e1->execute();
    double num2 = m_e2->execute();

    if (num1 < num2)
    {
      return 1;
    }
    return 0;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_eq : public Expression
{
public:
  Expr_eq(Expression* e1, Expression* e2)
  {
    m_e1 = e1;
    m_e2 = e2;
  }
  
  virtual double execute()
  {
	if (!m_e1 || !m_e2)
	  return 0;
	  
    double num1 = m_e1->execute();
    double num2 = m_e2->execute();

    if (float_eq(num1, num2))
    {
      return 1;
    }
    return 0;
  }

protected:
  Expression* m_e1;
  Expression* m_e2;
};

class Expr_while : public Expression
{
public:
  Expr_while(Expression* con, Expression* e)
  {
    m_con = con;
    m_e = e;
  }
  
  virtual double execute()
  {
	if (!m_con || !m_e)
	  return 0;
	
    double ace = m_con->execute();

    while (!float_eq(ace, 0))
    {
      m_e->execute();
      ace = m_con->execute();
    }

    return 0;
  }

protected:
  Expression* m_con;
  Expression* m_e;
};

class Expr_block : public Expression
{
public:
  Expr_block(Expressions* exprs)
  {
    m_exprs = exprs;
  }
  
  virtual double execute()
  {
	if (!m_exprs)
	  return 0;
    return m_exprs->execute();
  }

protected:
  Expressions* m_exprs;
};

void Execute(Expression* e)
{
  if (e)
	printf("%0.2lf\n", e->execute());
}

void Execute(Expressions* exprs)
{
  if (exprs)
    exprs->execute();
}

Expression* t_id(char* name)
{
  return new Expr_ID(name);
}

Expression* t_num(double num)
{
  return new Expr_num(num);
}

Expression* t_assign(char* name, Expression* e)
{
  return new Expr_assign(name, e);
}

Expression* t_plus(Expression* e1, Expression* e2)
{
  return new Expr_plus(e1, e2);
}

Expression* t_sub(Expression* e1, Expression* e2)
{
  return new Expr_sub(e1, e2);
}

Expression* t_mul(Expression* e1, Expression* e2)
{
  return new Expr_mul(e1, e2);
}

Expression* t_div(Expression* e1, Expression* e2)
{
  return new Expr_div(e1, e2);
}

Expression* t_if(Expression* con, Expression* et, Expression* ef)
{
  return new Expr_if(con, et, ef);
}

Expression* t_less(Expression* e1, Expression* e2)
{
  return new Expr_less(e1, e2);
}

Expression* t_eq(Expression* e1, Expression* e2)
{
  return new Expr_eq(e1, e2);
}

Expression* t_while(Expression* con, Expression* e)
{
  return new Expr_while(con, e);
}

Expression* t_block(Expressions* exprs)
{
  return new Expr_block(exprs);
}

Expressions* t_single_exprs(Expression* e)
{
  return new Expressions(e);
}

Expressions* t_append_exprs(Expressions* exprs, Expression* e)
{
  if (exprs && e)
	exprs->push(e);
  return exprs;
}
