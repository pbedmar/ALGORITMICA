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

    //C�lculo de la matriz traspuesta
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
	//Declaraci�n de variables
	int i;
	int j;
	srandom(time(0));

	//Comprobaci�n del n�mero de par�metros
	if (argc != 2)
    {
    	cerr << "Formato: " << argv[0] << " <n = 2^k>" << endl;
    	return -1;
    } 

    //Transformaci�n de n a entero
    int n = atoi(argv[1]);

    //Comprobaci�n de que el tama�o de la matriz es correcto
    if(log2(n) != (int)log2(n))
    {
    	cerr << "Error: n debe ser 2^k" << endl;
      	return -1;
    }

    //Generaci�n de la matriz dim�mica de tama�o n*n
    int **m = new int*[n];
    for(i=0; i<n; i++)
    {
    	m[i] = new int[n];
    }

    //Asignaci�n de valores a cada coordenada de la matriz de forma aleatoria
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
	
	//Imrpesi�n de la matriz
	cout << "La matriz traspuesta es:" << endl << endl;
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			cout << m[i][j] << "\t";
		}
		cout << endl << endl;
	}

	//Liberaci�n de memoria
	for(i=0; i<n; i++)
	{
    	delete[] m[i];
    }

    delete[] m;

	return 0;
}
