#!/bin/bash
let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv $i >> salida_mtdyv1.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv $i >> salida_mtdyv2.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv $i >> salida_mtdyv3.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv $i >> salida_mtdyv4.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv $i >> salida_mtdyv5.txt
  let i=$i*2
  let count=$count+1
done
