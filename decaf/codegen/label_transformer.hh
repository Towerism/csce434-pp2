#include <string>

class Label_transformer {
public:
  static std::string get_for_function(std::string label);
  static std::string get_for_method(std::string class_name, std::string method_name);
  static std::string get_for_class(std::string class_name);
};
