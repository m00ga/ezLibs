rm -rf Debug

cmake -S ../. -B Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DEZLOGGER_BUILD_TESTS=On --no-warn-unused-cli

cmake --build Debug && ctest --test-dir Debug/ezLogger/tests
