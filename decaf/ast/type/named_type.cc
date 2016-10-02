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
