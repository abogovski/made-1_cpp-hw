SRCS=$(find -wholename "./src/*.c")
TESTS= $(find -wholename "./src/*.c")

cppcheck $SRCS -I ./include && clang-tidy -p ./ $SRCS $TESTS -warnings-as-errors="*"
exit $?
