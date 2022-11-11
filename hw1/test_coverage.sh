if [[ "$1" != "NO_BUILD" ]]; then
cmake -DENABLE_COVERAGE=1 -DBUILD_BIN=0 -DENABLE_SANITIZERS=0 . && make all
fi;

lcov -z --directory .
mkdir -p test_coverage

ctest
lcov -c --directory . --output-file test_coverage/coverage.info
genhtml test_coverage/coverage.info --output-directory test_coverage/
