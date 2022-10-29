#!/bin/bash

EXECUTABLE=./QC-32
TESTFILES=./input/test/*.qc

for file in $TESTFILES
do
  #echo "Processing file $file"
  $EXECUTABLE $file > "$file.out"
  DIFF_RESULT=$(diff "$file.out" "$file.expected")
  echo $DIFF_RESULT
  if [ -z "$DIFF_RESULT" ];
  then
    printf "$file \U1F973\n"
  else
    printf "$file \U1F4A5\n"
  fi
done

echo $TESTPATH
