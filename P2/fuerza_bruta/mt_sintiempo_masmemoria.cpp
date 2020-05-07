/*Haz un programa que pida una matriz al usuario, preguntando cuantas componentes, haga su traspuesta
y luego imprima la matriz por pantalla.*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
using namespace std;

void matrizTraspuesta(int **m,int tam){

	int **m_traspuesta = new int*[tam];
    for(int i=0; i<tam; i++)
    {
    	m_traspuesta[i] = new int[tam];
    }

    //Cálculo de la matriz traspuesta
	for (int i=0; i<tam; i++)
	{
		for (int j=0; j<tam; j++)
		{
			m_traspuesta[j][i] = m[i][j];
		}
	}

	//Copia de matriz traspuesta a la matriz original
	for (int i=0; i<tam; i++)
	{
		for (int j=0; j<tam; j++)
		{
			m[i][j] = m_traspuesta[i][j];
		}
	}

	for(int i=0; i<tam; i++)
	{
    	delete m_traspuesta[i];
    }

    delete[] m_traspuesta;
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

    //Comprobación de que el tamaño de la matriz es correcto
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

	cout << "La matriz normal es:" << endl << endl;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			cout << m[i][j] << "\t";
		}
		cout << endl << endl;
	}

	matrizTraspuesta(m,n);
	
	//Imrpesión de la matriz
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
