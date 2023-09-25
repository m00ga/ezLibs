rm -rf Debug

cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DEZLOGGER_BUILD_TESTS=On -GNinja --no-warn-unused-cli

ln -s Debug/compile_commands.json .

ninja -C Debug && ctest --test-dir Debug/ezLogger/tests
