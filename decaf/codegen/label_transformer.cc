#include "label_transformer.hh"

#include <sstream>
#include <iostream>

#include "linker.hh"
std::string Label_transformer::get_for_function(std::string label) {
  if (Linker::check_label_for_main_linkage(label))
    return std::string(label);
  std::ostringstream in;
  const char* prefix = "_F_";
  in << prefix << label;
  return std::string(in.str());
}

std::string Label_transformer::get_for_method(std::string class_name, std::string method_name) {
  std::ostringstream in;
  const char* prefix = "_M_";
  in << prefix << class_name << "_" << method_name;
  return  std::string(in.str());
}

std::string Label_transformer::get_for_class(std::string class_name) {
  std::ostringstream in;
  const char* prefix = "_C_";
  in << prefix << class_name;
  return std::string(in.str());
}
