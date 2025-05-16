platformio run -t compiledb
mkdir -p build && cd build
cmake ..
make
ctest
