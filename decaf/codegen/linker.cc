#include "linker.hh"

#include <util/errors.hh>


bool Linker::is_main_defined = false;
const std::string Linker::main_label = "main";

bool Linker::check_label_for_main_linkage(std::string label) {
  if (label == main_label) {
    is_main_defined = true;
    return true;
  }
  return false;
}

bool Linker::link() {
  if (!is_main_defined)
    return link_failure();
  return true;
}

bool Linker::link_failure() {
  ReportError::NoMainFound();
  return false;
}
