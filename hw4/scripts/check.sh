cd $(dirname $0)/..

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .
SRCS=$(find -wholename "*.cpp" -not -wholename "*/CMakeFiles/*")
cppcheck $SRCS --language=c++ && clang-tidy -p ./ $SRCS -warnings-as-errors="*" -extra-arg=-std=c++17
exit $?
