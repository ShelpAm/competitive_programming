#!/bin/bash

clang_out=build/clang_test
gcc_out=build/gcc_test

clang++ -std=c++20 ./templates/main.cpp -o $clang_out
g++ -std=c++20 ./templates/main.cpp -o $gcc_out

if [ ! -e ${clang_out} -o ! -e ${gcc_out} ]; then
  echo "false"
fi
echo "true"
