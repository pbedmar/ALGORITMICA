#!/bin/bash
let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mt $i >> salida_mt1.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mt $i >> salida_mt2.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mt $i >> salida_mt3.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mt $i >> salida_mt4.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mt $i >> salida_mt5.txt
  let i=$i*2
  let count=$count+1
done
