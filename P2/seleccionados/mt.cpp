/* 
    Fichero: mt.cpp
    Autores:    Joaquín García Venegas
                Joaquín Alejandro España Sánchez
                Pedro Bedmar López
                Alejandro Escalona García
    Fecha: 05/04/20
    Compilación: g++ mt.cpp -o mt
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//realiza la transposición por "fuerza bruta", y en cada iteración intercambia m[i][j] con m[j][i]
void matrizTraspuesta(int **m,int inicio_x,int inicio_y,int tam){ 

    for(int i=0;i<tam;i++)
    {
        for(int j=i;j<tam;j++)
        {
            int swap = m[i+inicio_x][j+inicio_y];
            m[i+inicio_x][j+inicio_y] = m[j+inicio_x][i+inicio_y];
            m[j+inicio_x][i+inicio_y] = swap;
        }
    }

}

int main (int argc, char * argv[]) 
{
	//Declaración de variables y semilla random()
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
	clock_t t_antes = clock();

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
