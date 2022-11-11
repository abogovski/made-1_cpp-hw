SRCS=$(find -wholename "./lib/*.c")
TEST=$(find -wholename "./tests/*.cpp")

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .
cppcheck $SRCS -I ./lib/include && clang-tidy -p . $SRCS $TESTS -warnings-as-errors="*"
exit $?
