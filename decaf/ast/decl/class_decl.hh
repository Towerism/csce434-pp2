#ifndef CLASS_DECL_H
#define CLASS_DECL_H

#include <ast/decl/decl.hh>
#include <ast/symbol_table.hh>
#include <ast/type/ast_type.hh>

#include <codegen/frame_allocator.hh>

#include <util/list.hh>

class ClassDecl : public Decl {
protected:
  List<Decl *> *members;
  NamedType *extends;
  List<NamedType *> *implements;
  Symbol_table symbol_table;
  List<const char *> vtable;

public:
  ClassDecl(Identifier *name, NamedType *extends, List<NamedType *> *implements,
            List<Decl *> *members);
  const char *GetPrintNameForNode() override { return "ClassDecl"; }
  void PrintChildren(int indentLevel) override;
  void build_table() override;
  void analyze(reasonT focus) override;
  void prepare_for_emission(CodeGenerator *codegen, Symbol_table *symbol_table);
  void emit(CodeGenerator *codegen, Frame_allocator *frame_allocator,
            Symbol_table *symbol_table) override;
  void set_parent(Symbol_table &other) override {
    symbol_table.set_parent(other);
  }
  Type *get_type() override { return new NamedType(id); }
  Type *get_extends() { return extends; }
  List<NamedType *> *get_implements() { return implements; }
  Symbol_table *get_table() { return &symbol_table; }

  int get_size() { return next_instance_variable_offset; }
  List<VarDecl *> *get_fields();

      private : Frame_allocator *field_allocator;

  ClassDecl *parent_class;
  void add_virtuals();
  void extend();

  void add_field(Decl *decl);
private:
  int next_instance_variable_offset = 0;

  List<FnDecl *> methods;
  List<FnDecl *> effective_methods;
  List<VarDecl *> fields;
};

#endif /* CLASS_DECL_H */
