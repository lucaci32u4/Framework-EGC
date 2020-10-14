#!/usr/bin/env bash

# ensure argument is a number
re='^[1-9][0-9]*$'
if ! [[ $1 =~ $re ]] ; then
  echo "Argument not a number"; exit 1
fi

# ensure laboratory exists and cd to it
ROOTDIR="$(realpath "$(dirname "$0")")"
LABDIR="$ROOTDIR/Source/Laboratoare"
LAB="$LABDIR/Laborator$1"
if ! [[ -d "$LAB" ]] ; then
  echo "$LAB does not exist"; exit 1
else
  # shellcheck disable=SC2164
  cd "$LABDIR"
fi

# ensure zip folder exists
ZIPDIR="$ROOTDIR/moodle"
if ! [[ -d "$ZIPDIR" ]] ; then
  mkdir "$ZIPDIR"
fi

# make zip
zip -r "$ZIPDIR/Laborator$1.zip" "Laborator$1"
