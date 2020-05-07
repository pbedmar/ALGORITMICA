/* 
    Fichero: mt.cpp
    Autores:    Joaqu�n Garc�a Venegas
                Joaqu�n Alejandro Espa�a S�nchez
                Pedro Bedmar L�pez
                Alejandro Escalona Garc�a
    Fecha: 05/04/20
    Compilaci�n: g++ mt.cpp -o mt
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//realiza la transposici�n por "fuerza bruta", y en cada iteraci�n intercambia m[i][j] con m[j][i]
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
	//Declaraci�n de variables y semilla random()
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

    //Comprobaci�n de que el tama�o de la matriz es pontencia de dos
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

    //Impresi�n matriz original
    cout << "La matriz normal es:" << endl << endl;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl << endl;
    }

    //C�lculo del tiempo de ejecuci�n y llamada a la funci�n del algoritmo
	clock_t t_antes = clock();

	matrizTraspuesta(m,0,0,n);

	clock_t t_despues = clock();
    //Si se desea imprimir el tiempo, descomentar este fragmento de c�digo y el siguiente
    //cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

    //Impresi�n matriz traspuesta
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
