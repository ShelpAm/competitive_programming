#!/bin/bash

function env_set() {
  mkdir env -p
  echo $2 > env/$1
}

function env_get() {
  cat env/$1
}

function all_env() {
  env_dir=${1:=env}
  if [[ -e $env_dir ]]; then
    for i in $(ls $env_dir); do
      echo $i: $(env_get $i)
    done
  fi
}
