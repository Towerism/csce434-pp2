#include "while_stmt.hh"

void WhileStmt::PrintChildren(int indentLevel) {
  test->Print(indentLevel+1, "(test) ");
  body->Print(indentLevel+1, "(body) ");
}
