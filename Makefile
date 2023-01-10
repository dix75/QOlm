clean: ## Clean project
	rm -rf .qt/
	rm -rf Testing/
	rm -rf _deps/
	rm -rf lib/
	rm -rf .cmake/
	rm -rf CMakeFiles/
	rm -f .ninja_deps
	rm -f .ninja_log
	rm -f CMakeCache.txt
	rm -f CTestTestfile.cmake
	rm -rf QOlm/
	rm -rf QOlm_autogen/
	rm -f build.ninja
	rm -f cmake_install.cmake
	rm -f libQOlm.a
	rm -rf tests/CMakeFiles/
	rm -f tests/CTestTestfile.cmake
	rm -rf tests/QOlm_Tests
	rm -f tests/QOlm_TestsQml
	rm -rf tests/QOlm_TestsQml_autogen/
	rm -rf tests/QOlm_Tests_autogen/
	rm -f tests/cmake_install.cmake
.PHONY: clean

init-tests: ## Init tests
	cmake -DQOLM_ENABLE_TESTS=ON . -G"Ninja"
.PHONY: init-tests

run-tests: ## Run tests
	cmake --build . --target QOlm_Tests --config Release -j1
	cmake --build . --target QOlm_TestsQml --config Release -j1
	ctest -C Release . --verbose --progress
.PHONY: run-tests

help: ## Display this help screen
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

