#!/bin/bash
source utils.sh

cpp_start_point='+69'

function usage() {
  echo Usage: solve.sh [--usage] [platform] [problem] [--force]
}

if [[ ${1-""} == "--usage" ]]; then
  usage
  exit 0
fi

suffix="cpp"
platform=${1-$(env_get platform)}
problem=${2-$(env_get problem)}
dir=$platform/$problem/
src=${dir}main.$suffix
template="main.cpp"

mkdir $dir -p
if [[ -e $src ]]; then
  cp $src ${src}.bak
  if [[ ${3-""} == "--force" ]]; then
    cp code_templates/main.cpp $src
  fi
else  
  cp code_templates/main.cpp $src
fi
nvim $src ${cpp_start_point}
env_set platform $platform
env_set problem $problem
