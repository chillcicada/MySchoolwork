#!/bin/bash

echo "| np | lg | Time (s) |"
echo "|----|----|----------|"

make main

for np in 1 2 4 8; do
  for lg in 64 128 256; do
    make -s change lg=$lg
    make -s main
    TIME_RESULT=$({ /usr/bin/time -f "%e" make run np=$np 2>&1; } 2>&1 | grep -v "make")
    echo "| $np | $lg | $TIME_RESULT |"
  done
done

make -s clean
