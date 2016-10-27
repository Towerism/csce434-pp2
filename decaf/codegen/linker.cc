#include "linker.hh"

#include <util/errors.hh>

#include <cstring>

bool Linker::is_main_defined = false;
const char* Linker::main_label = "main";

bool Linker::check_label_for_main_linkage(const char* label) {
  if (strcmp(label, main_label) == 0) {
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
