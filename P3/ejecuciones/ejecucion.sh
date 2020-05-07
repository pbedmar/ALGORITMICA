#!/bin/bash

mkdir graficos datos;
make

#---ALGORITMO DE CERCANIA---
./cercania tsp_escenarios_ejecucion/ulysses16.tsp > datos/salida-cercania-ulysses16.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/cercania-ulysses16.png';
plot 'datos/salida-cercania-ulysses16.txt' using 2:3 w lp lc 'red' lw 2 title 'cercania'; 
"

./cercania tsp_escenarios_ejecucion/ulysses22.tsp > datos/salida-cercania-ulysses22.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/cercania-ulysses22.png';
plot 'datos/salida-cercania-ulysses22.txt' using 2:3 w lp lc 'red' lw 2 title 'cercania';
"

./cercania tsp_escenarios_ejecucion/att48.tsp > datos/salida-cercania-att48.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/cercania-att48.png';
plot 'datos/salida-cercania-att48.txt' using 2:3 w lp lc 'red' lw 2 title 'cercania';
"
 

./cercania tsp_escenarios_ejecucion/a280.tsp > datos/salida-cercania-a280.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/cercania-a280.png';
plot 'datos/salida-cercania-a280.txt' using 2:3 w lp lc 'red' lw 2 title 'cercania'; 
"

#---ALGORITMO PROPIO-------
./propio tsp_escenarios_ejecucion/ulysses16.tsp > datos/salida-propio-ulysses16.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/propio-ulysses16.png';
plot 'datos/salida-propio-ulysses16.txt' using 2:3 w lp lc 'olive' lw 2 title 'propio'; 
"

./propio tsp_escenarios_ejecucion/ulysses22.tsp > datos/salida-propio-ulysses22.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/propio-ulysses22.png';
plot 'datos/salida-propio-ulysses22.txt' using 2:3 w lp lc 'olive' lw 2 title 'propio';
"

./propio tsp_escenarios_ejecucion/att48.tsp > datos/salida-propio-att48.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/propio-att48.png';
plot 'datos/salida-propio-att48.txt' using 2:3 w lp lc 'olive' lw 2 title 'propio';
"
 
./propio tsp_escenarios_ejecucion/a280.tsp > datos/salida-propio-a280.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/propio-a280.png';
plot 'datos/salida-propio-a280.txt' using 2:3 w lp lc 'olive' lw 2 title 'propio'; 
"

#----ALGORITMO DE INSERCION---
./insercion tsp_escenarios_ejecucion/ulysses16.tsp > datos/salida-insercion-ulysses16.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/insercion-ulysses16.png';
plot 'datos/salida-insercion-ulysses16.txt' using 2:3 w lp lc 'blue' lw 2 title 'insercion'; 
"

./insercion tsp_escenarios_ejecucion/ulysses22.tsp > datos/salida-insercion-ulysses22.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/insercion-ulysses22.png';
plot 'datos/salida-insercion-ulysses22.txt' using 2:3 w lp lc 'blue' lw 2 title 'insercion';
"

./insercion tsp_escenarios_ejecucion/att48.tsp > datos/salida-insercion-att48.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/insercion-att48.png';
plot 'datos/salida-insercion-att48.txt' using 2:3 w lp lc 'blue' lw 2 title 'insercion';
"
 

./insercion tsp_escenarios_ejecucion/a280.tsp > datos/salida-insercion-a280.txt
gnuplot -e "
set terminal png size 1024, 768;
set size ratio -1;
set output 'graficos/insercion-a280.png';
plot 'datos/salida-insercion-a280.txt' using 2:3 w lp lc 'blue' lw 2 title 'insercion'; 
"
