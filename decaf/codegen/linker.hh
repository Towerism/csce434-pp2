class Linker {
public:
  // returns whether the label would be used for main linkage
  static bool check_label_for_main_linkage(const char* label);

  // returns whether link was successful
  static bool link();

private:
  static bool is_main_defined;
  static const char* main_label;

  static bool link_failure();
};
