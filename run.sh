#!/bin/bash
source utils.sh

cpp_start_point='447'

problem=$(env_get problem)
src="${problem}/main.cpp"
out=./build/a.out
input="./build/input"
input_problem=$(env_get input_problem)

mkdir build -p
rm -f $out
clang++ -D DEBUG ${src} -g -std=c++26 -stdlib=libstdc++ -o ${out}
if [ -e ${out} ]; then
    # updates the input
    if [ "${input_problem}" != "${problem}" ] || [ ! -e ${input} ] || [ ! -s ${input} ]; then
      echo '' > ${input}
      nvim "${input}"
      env_set input_problem "${problem}"
    fi
    echo 'Program running...'
    cat ${input} | ${out}
else
    echo 'Compilation failed. Retrying...'
    read -n 1 -r -s -p $'Press any key to continue...'
    nvim ${src} +${cpp_start_point}
fi
