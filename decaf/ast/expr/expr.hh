#ifndef EXPR_H
#define EXPR_H

#include <ast/stmt/stmt.hh>

#include <ast/type/type.hh>

#include <arch/tac.hh>

class Expr : public Stmt {
public:
  Expr(yyltype loc) : Stmt(loc) {}
  Expr() : Stmt() {}
  virtual void analyze(Symbol_table* symbol_table, reasonT focus) override {}
  virtual Type* evaluate_type(Symbol_table* symbol_table) { return Type::errorType; };
  virtual yyltype* get_location_or_default(yyltype* loc) { return location; }

  Location* get_frame_location() { return frame_location; }

protected:
  Location* frame_location;
};

#endif /* EXPR_H */
