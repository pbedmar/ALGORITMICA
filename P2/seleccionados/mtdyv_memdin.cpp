/* 
    Fichero: mtdyv_memdin.cpp
    Autores:    Joaquín García Venegas
                Joaquín Alejandro España Sánchez
                Pedro Bedmar López
                Alejandro Escalona García
    Fecha: 05/04/20
    Compilación: g++ mtdyv_memdin.cpp -o mtdyv_memdin
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//Realiza la traspuesta aplicando Divide y Vencerás. Se aplica recursivamente a cuatro submatrices de tamaño n/2.
//A diferencia de el otro programa que aplica DyV, no trabaja con índices y siempre sobre la matriz original, sino que en cada
//iteración se crean cuatro submatrices nuevas. Esto hace que este algoritmo tenga un tiempo de ejecución mucho mayor
void matrizTraspuesta(int **m, int tam){
	if(tam !=1)
	{

        //Se reserva memoria para las cuatro submatrices
		int **m1 = new int*[tam/2];
		int **m2 = new int*[tam/2];
		int **m3 = new int*[tam/2];
		int **m4 = new int*[tam/2];
    	for(int i=0; i<tam/2; i++)
    	{
    		m1[i] = new int[tam/2];
    		m2[i] = new int[tam/2];
    		m3[i] = new int[tam/2];
    		m4[i] = new int[tam/2];
    	}

        //Se asigna a cada submatriz los valores que le corresponden
    	for(int i=0; i<tam/2; i++)
    	{
    		for(int j=0; j<tam/2; j++)
    		{
    			m1[i][j]=m[i][j];
    			m2[i][j]=m[i][j+tam/2];
    			m3[i][j]=m[i+tam/2][j];
    			m4[i][j]=m[i+tam/2][j+tam/2];
    		}
    	}

        //Se llama recursivamente, pasando como parámetros las submatrices y el tamaño de estas
		matrizTraspuesta(m1,tam/2);
		matrizTraspuesta(m2,tam/2);
		matrizTraspuesta(m3,tam/2);
		matrizTraspuesta(m4,tam/2);
		
        //Se combinan las submatrices, intercambiando la superior derecha por la inferior izquierda
		for(int i=0; i<tam/2; i++)
    	{
    		for(int j=0; j<tam/2; j++)
    		{
    			m[i][j]=m1[i][j];
    			m[i+tam/2][j]=m2[i][j];
    			m[i][j+tam/2]=m3[i][j];
    			m[i+tam/2][j+tam/2]=m4[i][j];
    		}
    	}

        //Se libera la memoria
    	for(int i=0; i<tam/2; i++)
    	{
    		delete[] m1[i];
    		delete[] m2[i];
    		delete[] m3[i];
    		delete[] m4[i];
    	}
    	delete[] m1;
    	delete[] m2;
    	delete[] m3;
    	delete[] m4;
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

	matrizTraspuesta(m,n);

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