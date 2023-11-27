#!/bin/bash
source utils.sh

platform=$(env_get platform)
problem=$(env_get problem)
dir=$platform/$problem/
src=${dir}main.cpp
out=./build/a.out

mkdir build -p
rm -f $out
clang++ $src -g -std=c++26 -stdlib=libstdc++ -o $out
if [ -e $out ]; then
    # clear
    echo 'Executable is running. Please input on demand.'
    $out
else
    echo Compilation error. Retrying...
    read -n 1 -r -s -p $'Press any key to continue...'
    nvim $src
fi
