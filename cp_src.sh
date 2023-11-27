#!/bin/bash
source utils.sh

platform=$(env_get platform)
problem=$(env_get problem)
dir=$platform/$problem/
src=${dir}main.cpp

cat $src | xsel --clipboard
