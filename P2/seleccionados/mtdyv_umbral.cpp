/* 
    Fichero: mtdyv_umbral.cpp
    Autores:    Joaquín García Venegas
                Joaquín Alejandro España Sánchez
                Pedro Bedmar López
                Alejandro Escalona García
    Fecha: 05/04/20
    Compilación: g++ mtdyv_umbral.cpp -o mtdyv_umbral
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;

//Si el tamaño de la matriz es mayor que el umbral se aplica DyV, si no, se aplica fuerza bruta.
const int UMBRAL = 1;

//realiza la transposición por "fuerza bruta", y en cada iteración intercambia m[i][j] con m[j][i]
void traspuestaFuerzaBruta(int **m,int inicio_x,int inicio_y,int tam){

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

//Realiza la traspuesta aplicando Divide y Vencerás si su tamaño es mayor que el umbral. Si no, aplica "fuerza bruta".
void matrizTraspuesta(int **m, int pos_inicial_x, int pos_inicial_y, int tam){
    if(tam <= UMBRAL){
        traspuestaFuerzaBruta(m,pos_inicial_x,pos_inicial_y,tam);
    }
    else
    {
        //Pasa como parámtros la matriz sobre la que trabajamos (es siempre la misma), la posición desde la que se
        //desea trasponer (fila y columna) y el tamaño de la submatriz.
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
