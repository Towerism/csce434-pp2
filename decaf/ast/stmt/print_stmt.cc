#include "print_stmt.hh"

#include <codegen/codegen.hh>
#include <util/utility.hh>

PrintStmt::PrintStmt(List<Expr*> *a) {
  Assert(a != NULL);
  (args=a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) {
  args->PrintAll(indentLevel+1, "(args) ");
}


void PrintStmt::analyze(Symbol_table* symbol_table, reasonT focus) {
  int i = 1;
  args->Apply([&](Expr* arg) {
      arg->analyze(symbol_table, focus);
    });
  args->Apply([&](Expr* arg) {
      auto arg_type = arg->evaluate_type(symbol_table);
      if (!arg_type->equal(Type::intType)
          && !arg_type->equal(Type::boolType)
          && !arg_type->equal(Type::stringType))
        ReportError::PrintArgMismatch(arg, i, arg_type);
      ++i;
    });
}

void PrintStmt::emit(CodeGenerator* codegen, Frame_allocator* frame_allocator, Symbol_table* symbol_table) {
  Expr* arg = *(args->begin());
  Type* arg_type = arg->evaluate_type(symbol_table);
  arg->emit(codegen, frame_allocator, symbol_table);
  Location* arg_location = arg->get_frame_location();

  codegen->GenBuiltInCall(PrintString, frame_allocator, arg_location);
}
