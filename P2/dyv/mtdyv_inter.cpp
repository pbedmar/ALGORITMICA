/*Haz un programa que pida una matriz al usuario, preguntando cuantas componentes, haga su traspuesta
y luego imprima la matriz por pantalla.*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <climits>
using namespace std;


void intercambiar (int **m,int fIniA, int cIniA, int fIniB, int cIniB, int dimen) {
    for (int i=0; i<=dimen-1; i++)
        for (int j=0; j<=dimen-1; j++) {
            int aux = m[fIniA+i][cIniA+j];
            m[fIniA+i][cIniA+j] = m[fIniB+i][cIniB+j];
            m[fIniB+i][cIniB+j] = aux;
        }
}

// void trasponerDyV1 (int **m, int fInicio, int fFin, int cInicio, int cFin) {
//     // caso basico de 1x1
//     if (fInicio<fFin) {
//         int fMedio = (fInicio+fFin)/2;
//         int cMedio = (cInicio+cFin)/2;
//         trasponerDyV1 (m, fInicio, fMedio, cInicio, cMedio);
//         trasponerDyV1 (m, fInicio, fMedio, cMedio+1, cFin);
//         trasponerDyV1 (m, fMedio+1, fFin, cInicio, cMedio);
//         trasponerDyV1 (m, fMedio+1, fFin, cMedio+1, cFin);
//         intercambiar (m, fMedio+1, cInicio, fInicio, cMedio+1, fFin-fMedio);
//     }
//  }

 void trasponerDyV1 (int **m, int fInicio, int fFin, int cInicio, int cFin) {
    // caso basico de 1x1
    if (fInicio-fFin>) {
        int fMedio = (fInicio+fFin)/2;
        int cMedio = (cInicio+cFin)/2;
        trasponerDyV1 (m, fInicio, fMedio, cInicio, cMedio);
        trasponerDyV1 (m, fInicio, fMedio, cMedio+1, cFin);
        trasponerDyV1 (m, fMedio+1, fFin, cInicio, cMedio);
        trasponerDyV1 (m, fMedio+1, fFin, cMedio+1, cFin);
        intercambiar (m, fMedio+1, cInicio, fInicio, cMedio+1, fFin-fMedio);
    }
 }

void trasponer (int **m, int tam) {
    trasponerDyV1 (m, 0, tam-1, 0, tam-1);
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

    // cout << "La matriz normal es:" << endl << endl;
    // for (i=0; i<n; i++)
    // {
    //     for (j=0; j<n; j++)
    //     {
    //         cout << m[i][j] << "\t";
    //     }
    //     cout << endl << endl;
    // }

    clock_t t_antes=clock();
	trasponer(m,n);
	clock_t t_despues = clock();
    cout << n << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;
	
    // cout << "La matriz traspuesta es:" << endl << endl;
    // for (i=0; i<n; i++)
    // {
    //     for (j=0; j<n; j++)
    //     {
    //         cout << m[i][j] << "\t";
    //     }
    //     cout << endl << endl;
    // }

	//Liberación de memoria
	for(i=0; i<n; i++)
	{
    	delete[] m[i];
    }

    delete[] m;

	return 0;
}
