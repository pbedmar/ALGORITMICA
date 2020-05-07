#!/bin/bash
let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv_masmemoria $i >> salida_mtdyv_memdin1.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv_masmemoria $i >> salida_mtdyv_memdin2.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv_masmemoria $i >> salida_mtdyv_memdin3.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv_masmemoria $i >> salida_mtdyv_memdin4.txt
  let i=$i*2
  let count=$count+1
done

let i=2
let count=0
while [ $count -lt 15 ];do
  echo $i
  ./mtdyv_masmemoria $i >> salida_mtdyv_memdin5.txt
  let i=$i*2
  let count=$count+1
done
