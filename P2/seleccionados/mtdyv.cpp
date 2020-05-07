/* 
    Fichero: mtdyv.cpp
    Autores:    Joaquín García Venegas
                Joaquín Alejandro España Sánchez
                Pedro Bedmar López
                Alejandro Escalona García
    Fecha: 05/04/20
    Compilación: g++ mtdyv.cpp -o mtdyv
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//Realiza la traspuesta aplicando Divide y Vencerás. Se aplica recursivamente a cuatro submatrices de tamaño n/2
//mientras que su tamaño sea mayor que 1.
void matrizTraspuesta(int **m, int pos_inicial_x, int pos_inicial_y, int tam){
    if(tam != 1)
    {

        //Pasa como parámtros la matriz sobre la que trabajamos (es siempre la misma, no se reservan submatrices nuevas),
        //la posición desde la que se desea trasponer (filas y columnas) y el tamaño de la submatriz.
        matrizTraspuesta(m,pos_inicial_x,pos_inicial_y,tam/2);
        matrizTraspuesta(m,pos_inicial_x+tam/2,pos_inicial_y,tam/2);
        matrizTraspuesta(m,pos_inicial_x,pos_inicial_y+tam/2,tam/2);
        matrizTraspuesta(m,pos_inicial_x+tam/2,pos_inicial_y+tam/2,tam/2);

        //Recompone las cuatro submatrices, cambiando la superior derecha por la inferior izquierda
        for(int i=0;i<tam/2;i++){
            for(int j=0;j<tam/2;j++){
                int swap = m[pos_inicial_x+i][pos_inicial_y+tam/2+j];
                m[pos_inicial_x+i][pos_inicial_y+tam/2+j] = m[pos_inicial_x+tam/2+i][pos_inicial_y+j];
                m[pos_inicial_x+tam/2+i][pos_inicial_y+j] = swap;
            }
        }
    }
}

int main (int argc, char * argv[]) 
{
	//Declaración de variables
	int i;
	int j;
	srandom(time(0));

	//Comprobación del número de parámetros
	if (argc != 2)
    {
    	cerr << "Formato: " << argv[0] << " <n = 2^k>" << endl;
    	return -1;
    } 

    //Transformación de n a entero
    int n = atoi(argv[1]);

    //Comprobación de que el tamaño de la matriz es pontencia de dos
    if(log2(n) != (int)log2(n))
    {
    	cerr << "Error: n debe ser 2^k" << endl;
      	return -1;
    }

    //Generación de la matriz dimámica de tamaño n*n
    int **m = new int*[n];
    for(i=0; i<n; i++)
    {
    	m[i] = new int[n];
    }

    //Asignación de valores a cada coordenada de la matriz de forma aleatoria
    for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			m[i][j] = (rand() % 1000) + 1;
		}
	}

    //Impresión matriz original
    cout << "La matriz normal es:" << endl << endl;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl << endl;
    }

    //Cálculo del tiempo de ejecución y llamada a la función del algoritmo
    clock_t t_antes=clock();

	matrizTraspuesta(m,0,0,n);

	clock_t t_despues = clock();
    //Si se desea imprimir el tiempo, descomentar este fragmento de código y el siguiente
    //cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

    //Impresión matriz traspuesta
    cout << "La matriz traspuesta es:" << endl << endl;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl << endl;
    }
	

	//Liberación de memoria
	for(i=0; i<n; i++)
	{
    	delete[] m[i];
    }

    delete[] m;

	return 0;
}
