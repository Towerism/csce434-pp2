#include "error_message_factory.hh"

#include <cstring>

#include <sstream>

const std::string
    Error_message_factory::error_messages[(int)Runtime_error::_Count_] = {
        "Decaf runtime error: Array size is <= 0",
        "Decaf runtime error: Array subscript out of bounds"};

char *Error_message_factory::for_runtime_error(Runtime_error error) {
  auto message = error_messages[(int)error];

  std::ostringstream in;

  in << message << "\\n";
  return strdup(in.str().c_str());
}
