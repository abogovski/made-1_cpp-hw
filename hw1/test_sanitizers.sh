if [[ "$1" != "NO_BUILD" ]]; then
cmake -DBUILD_BIN=0 -DENABLE_SANITIZERS=1 -DENABLE_COVERAGE=0 . && make all
fi;

make test
