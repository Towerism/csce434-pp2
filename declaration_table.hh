#ifndef DECLARATION_TABLE_H
#define DECLARATION_TABLE_H

#include <string>
#include <unordered_map>

template <typename decl_t>
class Declaration_table {
public:
  void declare(decl_t* declaration) {
    std::string name = declaration->getName();
    declarations[name] = declaration;
  }

  decl_t* contains(std::string name) {
    auto key_value = declarations.find(name);
    if (key_value != declarations.end())
      return key_value->second;
    return nullptr;
  }
private:
  std::unordered_map<std::string, decl_t*> declarations;
};

#endif // DECLARATION_TABLE_H
