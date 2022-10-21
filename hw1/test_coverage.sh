cmake . && make all

lcov -z --directory .
make test
lcov -c --directory . --output-file test_coverage/coverage.info
genhtml test_coverage/coverage.info --output-directory test_coverage/
