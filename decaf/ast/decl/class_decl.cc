#include "class_decl.hh"

#include <ast/decl/ast_decl.hh>
#include <ast/type/named_type.hh>

#include <codegen/label_transformer.hh>

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType *> *imp,
                     List<Decl *> *m)
    : Decl(n) {
  // extends can be NULL, impl & mem may be empty lists but cannot be NULL
  Assert(n != NULL && imp != NULL && m != NULL);
  extends = ex;
  if (extends)
    extends->SetParent(this);
  (implements = imp)->SetParentAll(this);
  (members = m)->SetParentAll(this);
  symbol_table.set_this_type(new NamedType(id));
}

void ClassDecl::PrintChildren(int indentLevel) {
  id->Print(indentLevel + 1);
  if (extends)
    extends->Print(indentLevel + 1, "(extends) ");
  implements->PrintAll(indentLevel + 1, "(implements) ");
  members->PrintAll(indentLevel + 1);
}

void ClassDecl::build_table() {
  members->Apply([&](Decl *decl) { symbol_table.declare(decl); });
  members->Apply([&](Decl *decl) { decl->build_table(); });
  add_virtuals();
  members->Apply([&](Decl *decl) {
    symbol_table.check_virtual(decl);
    decl->set_parent(symbol_table);
  });
}

void ClassDecl::add_virtuals() {
  implements->Apply([&](NamedType *type) {
    auto interface = Program::symbol_table.get_interface(type->getName());
    if (interface) {
      auto members = interface->get_members();
      members->Apply([&](Decl *member) {
        symbol_table.add_virtual(type, dynamic_cast<FnDecl *>(member));
      });
    }
  });
}

void ClassDecl::analyze(reasonT focus) {
  extend();
  members->Apply([&](Decl *decl) { symbol_table.check_super(decl); });
  implements->Apply(
      [&](NamedType *type) { type->analyze(LookingForInterface); });
  members->Apply([&](Decl *decl) { decl->analyze(LookingForType); });
  symbol_table.check_virtuals_implemented(this, implements);
}

void ClassDecl::extend() {
  if (extends) {
    extends->analyze(LookingForClass);
    auto superClass = Program::symbol_table.get_class(extends->getName());
    if (superClass) {
      symbol_table.set_super(superClass->symbol_table);
      parent_class = superClass;
    }
  }
}

void ClassDecl::prepare_for_emission(CodeGenerator *codegen,
                                     Symbol_table *symbol_table) {
  if (field_allocator)
    return;
  if (extends) {
    parent_class->prepare_for_emission(codegen, symbol_table);
    auto parent_methods = parent_class->methods;
    auto parent_fields = parent_class->get_fields();
    methods.CopyFrom(&parent_methods);
    fields.CopyFrom(parent_fields);
    field_allocator = new Frame_allocator(*parent_class->field_allocator);
  } else {
    field_allocator = new Frame_allocator(fpRelative, Frame_growth::Upwards);
  }
  field_allocator->allocate(4, strdup("vtable"));
  FnDecl *method = nullptr;
  VarDecl *field = nullptr;
  members->Apply([&](Decl *decl) {
    method = dynamic_cast<FnDecl *>(decl);
    if (method) {
      int j;
      for (j = 0; j < methods.NumElements(); ++j) {
        if (method->matches_prototype(methods.Nth(j))) {
          methods.RemoveAt(j);
          methods.InsertAt(method, j);
          method->set_offset(j);
          method->set_label_override(getName().c_str());
          effective_methods.Append(method);
          break;
        }
      }
      if (j >= methods.NumElements()) {
        method->set_is_method();
        method->set_offset(methods.NumElements());
        methods.Append(method);
        effective_methods.Append(method);
      }
    } else {
      field = dynamic_cast<VarDecl *>(decl);
      fields.Append(field);
      field->emit(codegen, field_allocator, &this->symbol_table);
    }
  });
}

void ClassDecl::emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
                     Symbol_table *symbol_table) {
  effective_methods.Apply([&](FnDecl *function) {
    function->emit(codegen, field_allocator, symbol_table);
  });
  methods.Apply(
      [&](FnDecl *function) { vtable.Append(function->get_label()); });
  codegen->GenVTable(getName().c_str(), &vtable);
}

List<VarDecl *> *ClassDecl::get_fields() {
  List<VarDecl *> *result = new List<VarDecl *>();
  members->Apply([&](Decl *decl) {
    auto variable = dynamic_cast<VarDecl *>(decl);
    if (variable)
      result->Append(variable);
  });
  return result;
}
