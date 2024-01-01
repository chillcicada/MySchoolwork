#!/bin/sh
for ((j=1; j<=2; j++))
do
  fn= "file${j}.txt"
  for ((i=1; i<=10; i++))
  do
    sed -i "s/filename=.*/filename=${fn}/" input.nml
    sed -i "s/maxElements=.*/maxElements=${i}/" input.nml
    make dev
  done
done
