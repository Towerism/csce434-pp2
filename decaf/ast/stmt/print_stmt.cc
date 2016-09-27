#include "print_stmt.hh"

#include <util/utility.hh>

PrintStmt::PrintStmt(List<Expr*> *a) {
  Assert(a != NULL);
  (args=a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) {
  args->PrintAll(indentLevel+1, "(args) ");
}
