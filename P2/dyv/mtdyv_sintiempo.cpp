/*Haz un programa que pida una matriz al usuario, preguntando cuantas componentes, haga su traspuesta
y luego imprima la matriz por pantalla.*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//Si el tamaño de la matriz es mayor o igual que umbral se aplica DyV, si no, se aplica fuerza bruta.
const int UMBRAL = 2048;

void traspuestaFuerzaBruta(int **m,int inicio_x,int inicio_y,int tam){  //tamaño ya es el del cuadrante

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

void matrizTraspuesta(int **m, int pos_inicial_x, int pos_inicial_y, int tam){
    if(tam < UMBRAL)
    {
        traspuestaFuerzaBruta(m,pos_inicial_x,pos_inicial_y,tam);
    } 
    else
    {

        matrizTraspuesta(m,pos_inicial_x,pos_inicial_y,tam/2);
        matrizTraspuesta(m,pos_inicial_x+tam/2,pos_inicial_y,tam/2);
        matrizTraspuesta(m,pos_inicial_x,pos_inicial_y+tam/2,tam/2);
        matrizTraspuesta(m,pos_inicial_x+tam/2,pos_inicial_y+tam/2,tam/2);

        for(int i=0;i<tam/2;i++)
        {
            for(int j=i;j<tam/2;j++){
                int swap = m[pos_inicial_x+i][pos_inicial_y+j];
                m[pos_inicial_x+i][pos_inicial_y+j] = m[pos_inicial_x+j][pos_inicial_y+i];
                m[pos_inicial_x+j][pos_inicial_y+i] = swap;
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

	matrizTraspuesta(m,0,0,n);
	
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