#include "type.hh"

#include <util/utility.hh>

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType = new Type("void");
Type *Type::boolType = new Type("bool");
Type *Type::nullType = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType = new Type("error");

Type::Type(const char *n) {
  Assert(n);
  typeName = strdup(n);
}

void Type::PrintChildren(int indentLevel) { printf("%s", typeName); }

bool Type::equal(Type *other) {
if (other == Type::errorType
      || this == Type::errorType
      || other == Type::nullType
      || this == Type::nullType)
  return true;
if (!typeName || !other->typeName)
  return false;
return strcmp(typeName, other->typeName) == 0;
}
