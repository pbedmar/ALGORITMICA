#!/bin/bash
echo "" > salida.dat
let i=10
let count=0
> salida.dat
while [ $count -lt 25 ];do
  echo $i
  ./hanoiO3 $i >> salida_hanoiO3.dat
  let i=$i+1
  let count=$count+1
done
