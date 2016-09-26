MAKE := make -s
BUILD_DIR := build
GENERATOR := Unix Makefiles
CMAKE_FLAGS :=

.PHONY:: all test cmake-test-flags run-tests \
         coverage cmake-coverage-flags build-coveralls \
         compile build-dir generate clean clean-build

.DEFAULT:: all
all:: ##same as test
all:: test


test:: ##compile and run test suite
test run-tests:: compile
	@$(MAKE) run-tests -C $(BUILD_DIR)
test-scope:: compile
	@$(MAKE) test-scope -C $(BUILD_DIR)
test-syntax:: compile
	@$(MAKE) test-syntax -C $(BUILD_DIR)


compile:: ##just compile
compile generate build-dir::
	@mkdir -p $(BUILD_DIR)
compile generate::
	@cd $(BUILD_DIR) && cmake $(CMAKE_FLAGS) -G"$(GENERATOR)" ..
compile::
	@$(MAKE) -C $(BUILD_DIR)


clean:: ##clean build system
	@echo "-- Cleaning"
clean clean-build::
	@echo "-- Removing Build Directory"
	@rm -rf $(BUILD_DIR)
clean::
	@echo "-- Done"


help:: ##show this help
	@echo "The following are some of the valid targets for this Makefile:"
help display-doublehash-help-comments::
	@sed -n '/##/p' $(MAKEFILE_LIST) \
   | sed -e '/sed/d' -e 's/##//' -e 's/^/\.\.\. /' -e 's/ /+/g' -e 's/::/ +-/g' \
   | column -t -s " " | sed 's/+/ /g'
