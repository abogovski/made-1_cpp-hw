if [[ "$1" != "NO_BUILD" ]]; then
cmake -DBUILD_BIN=0 -DENABLE_COVERAGE=0 -DENABLE_SANITIZERS=0 . && make all
fi;

lcov -z --directory .
mkdir test_coverage

for test_file in ./tests/*_tests;
do
    valgrind --error-exitcode=1 $test_file
    if [[ "$?" != "0" ]]; then
        exit 1
    fi
done;
