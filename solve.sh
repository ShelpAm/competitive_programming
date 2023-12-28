#!/bin/bash
source utils.sh

cpp_start_point='168'

function usage() {
  echo 'Usage: solve.sh [--usage] [path/to/problem/] [--force]'
}

if [[ ${1-""} == "--usage" ]]; then
  usage
  exit 0
fi

problem="${1:-$(env_get problem)}"
src=${problem}/main.cpp

mkdir ${problem} -p
if [[ -e ${src} ]]; then
  cp ${src} ${src}.bak
  if [[ ${2-""} == "--force" ]]; then
    cp code_templates/main.cpp ${src}
  fi
else  
  cp code_templates/main.cpp ${src}
fi
nvim $src +${cpp_start_point}
env_set problem ${problem}
