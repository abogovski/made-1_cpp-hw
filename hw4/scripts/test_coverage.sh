cd $(dirname $0)/..

cmake -DTEST_COVERAGE=1 . && make

lcov -z --directory sequential_static_lib --directory parallel_shared_lib
make test

mkdir -p test_coverage
lcov -c --directory sequential_static_lib --directory parallel_shared_lib --output-file test_coverage/coverage.info
lcov -r test_coverage/coverage.info "/usr*" -o test_coverage/coverage.info
genhtml test_coverage/coverage.info --output-directory test_coverage/
