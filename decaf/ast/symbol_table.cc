#include "symbol_table.hh"

#include <algorithm>

#include <util/errors.hh>
#include <util/utility.hh>

#include "decl/ast_decl.hh"

void Symbol_table::declare(Decl* declaration) {
  detect_previous_declaration(declaration);
  classes.maybe_declare(declaration);
  interfaces.maybe_declare(declaration);
  variables.maybe_declare(declaration);
  functions.maybe_declare(declaration);
}

void Symbol_table::add_virtual(NamedType* interface_type, Decl* declaration) {
  Decl* prev_decl = virtuals.contains(declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(declaration, prev_decl);
  auto function_declaration = dynamic_cast<FnDecl*>(declaration);
  virtuals.add(interface_type->getName(), function_declaration);
}

void Symbol_table::detect_previous_declaration(Decl* new_declaration) {
  Decl* prev_decl = variables.contains(new_declaration->getName());
  if (!prev_decl) {
    prev_decl = functions.contains(new_declaration->getName());
  }
  if (!prev_decl)
    prev_decl = classes.contains(new_declaration->getName());
  if (!prev_decl)
    prev_decl = interfaces.contains(new_declaration->getName());
  if (prev_decl)
    ReportError::DeclConflict(new_declaration, prev_decl);
}

void Symbol_table::check_virtual(Decl* declaration) {
  auto virtual_function = virtuals.contains(declaration->getName());
  auto function = dynamic_cast<FnDecl*>(declaration);
  if (virtual_function && !function->matches_signature(virtual_function))
    ReportError::OverrideMismatch(function);
}

void Symbol_table::check_super(Decl* declaration) {
  auto function = dynamic_cast<FnDecl*>(declaration);
  if (function) {
    auto super_function = find_inherited_function(function->getName());
    if (super_function && !function->matches_signature(super_function))
      ReportError::OverrideMismatch(function);
  }
  auto variable = dynamic_cast<VarDecl*>(declaration);
  if (variable) {
    auto super_variable = find_inherited_variable(variable->getName());
    if (super_variable)
      ReportError::DeclConflict(declaration, super_variable);
  }
}

void Symbol_table::check_virtuals_implemented(ClassDecl* class_decl, List<NamedType*>* interface_types) {
  interface_types->Apply([&](NamedType* type) {
      auto interface = Program::symbol_table.get_interface(type->getName());
      if (!interface) {
        return;
      }
      auto interface_virtuals = virtuals.get_functions(type->getName());
      if (!interface_virtuals)
        return;
      bool not_fully_implemented = std::any_of(interface_virtuals->begin(), interface_virtuals->end(), [&](std::pair<std::string, FnDecl*> key_function) {
          auto function = key_function.second;
          auto function_implemented = functions.contains(function->getName());
          if (nullptr == function_implemented)
            function_implemented = find_inherited_function(function->getName());
          return nullptr == function_implemented;
        });
      if (not_fully_implemented)
        ReportError::InterfaceNotImplemented(class_decl, type);
    });
}

FnDecl* Symbol_table::find_inherited_function(std::string name) {
  if (!super)
    return nullptr;
  auto current = super;
  do {
      auto super_function = current->functions.contains(name);
      if (super_function)
        return super_function;
    current = current->super;
  } while(current != nullptr);
  return nullptr;
}

VarDecl* Symbol_table::find_inherited_variable(std::string name) {
  if (!super)
    return nullptr;
  auto current = super;
  do {
    auto super_variable = current->variables.contains(name);
    if (super_variable)
      return super_variable;
    current = current->super;
  } while(current != nullptr);
  return nullptr;
}

VarDecl* Symbol_table::find_parent_variable(std::string name) {
  if (!parent)
    return nullptr;
  auto current = parent;
  do {
    auto parent_variable = current->variables.contains(name);
    if (parent_variable)
      return parent_variable;
    current = current->parent;
  } while(current != nullptr);
  return nullptr;
}

bool Symbol_table::type_exists(std::string name) {
  return classes.contains(name) || interfaces.contains(name);
}

ClassDecl* Symbol_table::get_class(std::string name) {
  return classes.contains(name);
}

InterfaceDecl* Symbol_table::get_interface(std::string name) {
  return interfaces.contains(name);
}

VarDecl* Symbol_table::check_variable_declared(Identifier* identifier, std::function<void()> error_action) {
  auto current = this;
  do {
    auto variable = current->variables.contains(identifier->getName());
    if (!variable)
      variable = current->find_parent_variable(identifier->getName());
    if (!variable)
      variable = current->find_inherited_variable(identifier->getName());
    if (variable)
      return variable;
    current = current->parent;
  } while(current != nullptr);
  error_action();
  auto error_decl = new VarDecl(identifier, Type::errorType);
  variables.declare(error_decl);
  return error_decl;
}

FnDecl* Symbol_table::check_function_declared(Identifier* identifier, std::function<void()> error_action) {
  auto current = this;
  do {
    auto function = current->functions.contains(identifier->getName());
    if (!function)
      function = current->find_inherited_function(identifier->getName());
    if (function)
      return function;
    current = current->parent;
  } while(current != nullptr);
  error_action();
  return nullptr;
}

bool Symbol_table::check_function_args_length(Identifier* identifier,
                                              List<Expr*>* actuals,
                                              std::function<void(int, int)> error_action) {
  auto function = check_function_declared(identifier);
  if (!function)
    return false;
  auto formals = function->get_formals();
  auto given = actuals->NumElements();
  auto expected = formals->NumElements();
  if (given != expected) {
    error_action(expected, given);
    return false;
  }
  return true;
}

bool Symbol_table::check_function_args(Identifier* identifier, List<Expr*>* args,
                                       List<Type*>* arg_types,
                                       std::function<void(Expr*, int, Type*, Type*)> error_action) {
  bool good = true;
  auto function = check_function_declared(identifier);
  auto formals = function->get_formals();
  int i = 0;
  formals->Apply([&](VarDecl* decl) {
      auto arg = args->Nth(i);
      auto expected_type = decl->getType();
      auto given_type = arg_types->Nth(i);
      if (!given_type->coerce(expected_type, this)) {
        error_action(arg, i+1, given_type, expected_type);
        good = false;
      }
      ++i;
    });
  return good;
}


Type* Symbol_table::find_return_type() {
  auto current = this;
  do {
    if (current->return_type)
      return current->return_type;
    current = current->parent;
  } while(current != nullptr);
  return nullptr;
}

Type* Symbol_table::find_this_type() {
  auto current = this;
  do {
    if (current->this_type)
      return current->this_type;
    current = current->parent;
  } while(current != nullptr);
  return nullptr;
}

bool Symbol_table::class_extends_type(Type* class_identifier, Type* extends) {
  Type* current_extends = nullptr;
  List<NamedType*>* current_implements;
  std::string class_name = class_identifier->getName();
  do {
    auto class_decl = Program::symbol_table.get_class(class_name);
    if (!class_decl)
      return false;
    current_extends = class_decl->get_extends();
    current_implements = class_decl->get_implements();
    if (( current_extends && current_extends->equal(extends))
        || std::find_if(current_implements->begin(), current_implements->end(),
                        [&](NamedType* implements) {
                          return implements->equal(extends);
                        }) != current_implements->end())
      return true;
    if (current_extends)
      class_name = current_extends->getName();
  } while(current_extends != nullptr);
  return false;
}

Symbol_table* Symbol_table::get_table_for_functions(Type* type) {
  auto class_decl = Program::symbol_table.classes.contains(type->getName());
  if (class_decl)
    return class_decl->get_table();
  auto interface_decl = Program::symbol_table.interfaces.contains(type->getName());
  if (interface_decl)
    return interface_decl->get_table();
  return nullptr;
}

Symbol_table* Symbol_table::get_table_for_variables(Type* type) {
  auto class_decl = Program::symbol_table.classes.contains(type->getName());
  if (class_decl)
    return class_decl->get_table();
  return nullptr;
}
