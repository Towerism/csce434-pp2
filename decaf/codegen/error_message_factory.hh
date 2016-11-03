#include <string>

enum class Runtime_error : int { Array_size, Array_subscript, _Count_ };

class Error_message_factory {
public:
  static char *for_runtime_error(Runtime_error error);

private:
  static const std::string error_messages[(int)Runtime_error::_Count_];
};
