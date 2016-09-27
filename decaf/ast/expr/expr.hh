#ifndef EXPR_H
#define EXPR_H

#include <ast/stmt/stmt.hh>

class Expr : public Stmt {
public:
  Expr(yyltype loc) : Stmt(loc) {}
  Expr() : Stmt() {}
};

#endif /* EXPR_H */
