#!/bin/bash

clang_out=build/clang_test
gcc_out=build/gcc_test

rm -f $clang_out $gcc_out

clang++ -std=c++17 -stdlib=libc++ ./templates/main.cpp -o $clang_out -Werror -Wall -Wextra
g++ -std=c++17 -lstdc++ ./templates/main.cpp -o $gcc_out

if [ ! -e ${clang_out} ]; then
  echo clang++ false
elif [ ! -e ${gcc_out} ]; then
  echo g++ false
else
  echo true
fi

