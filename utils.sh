#!/bin/bash

state_home=${XDG_STATE_HOME:=${HOME}/.local/state}/template_environment

function env_set() {
  mkdir ${state_home} -p
  echo ${2} > ${state_home}/$1
}

function env_get() {
  if [ -e "${state_home}/$1" ]; then
    cat "${state_home}/$1"
  else
    echo ''
  fi
}

function all_env() {
  if [[ -e ${state_home} ]]; then
    for i in $(ls ${state_home}); do
      echo "$i: $(env_get $i)"
    done
  fi
}
