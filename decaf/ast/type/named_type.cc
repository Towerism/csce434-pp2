#include "named_type.hh"

#include <ast/stmt/program.hh>
#include <util/utility.hh>

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
  Assert(i != NULL);
  (id=i)->SetParent(this);
}

void NamedType::PrintChildren(int indentLevel) {
  id->Print(indentLevel+1);
}

void NamedType::analyze(reasonT focus) {
  if (!Program::symbol_table.type_exists(id->getName()))
    ReportError::IdentifierNotDeclared(id, focus);
}

bool NamedType::coerce(Type* type, Symbol_table* symbol_table) {
  bool exact_match = equal(type);
  return exact_match || symbol_table->class_extends_type(this, type);
}
