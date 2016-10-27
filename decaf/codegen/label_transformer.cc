#include "label_transformer.hh"

#include <sstream>
#include <iostream>

std::string Label_transformer::get_for_function(std::string label) {
  std::ostringstream in;
  const char* prefix = "F_";
  in << prefix << label;
  return in.str();
}
