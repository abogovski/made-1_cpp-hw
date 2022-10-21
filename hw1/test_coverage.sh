cmake -DENABLE_COVERAGE=1 . && make all

lcov -z --directory .
make test
mkdir test_coverage
lcov -c --directory . --output-file test_coverage/coverage.info
genhtml test_coverage/coverage.info --output-directory test_coverage/
