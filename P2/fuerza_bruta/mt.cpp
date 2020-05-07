/*Haz un programa que pida una matriz al usuario, preguntando cuantas componentes, haga su traspuesta
y luego imprima la matriz por pantalla.*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

void matrizTraspuesta(int **m,int inicio_x,int inicio_y,int tam){  //tama�o ya es el del cuadrante

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

	clock_t t_antes = clock();
	matrizTraspuesta(m,0,0,n);
	clock_t t_despues = clock();
    cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

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
