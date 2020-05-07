#!/bin/bash
let i=2000000
let count=0
while [ $count -lt 25 ];do
  echo $i
  ./mergesort $i >> salida_mergesort_saltos.dat
  let i=$i+400000
  let count=$count+1
done
