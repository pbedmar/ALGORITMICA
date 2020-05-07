/*Haz un programa que pida una matriz al usuario, preguntando cuantas componentes, haga su traspuesta
y luego imprima la matriz por pantalla.*/

#include <iostream>
using namespace std;

int main () {
	//Declaración de variables e introducción de dimensión de la matriz.
	int fil;
	int col;
	int i;
	int j;
	int filasGuardadas;
	int columnasGuardadas;
	
	cout << "Introduce el numero de filas:\n";
	cin >> fil;
	cout << "Introduce el numero de columnas:\n";
	cin >> col;
	int matrix [fil][col];
	int matrixTraspuesta [col][fil];
	
	//Asignación de valores a cada coordenada de la matriz
	for (i=0; i<fil; i++){
		for (j=0; j<col; j++){
			cout << "Inserta la coordenada de la fila " << i+1 << " correspondiente a la columna " << j+1 << ":\n";
			cin >> matrix [i][j];
			matrixTraspuesta [j][i] = matrix [i][j];
			
		}
	}
	
	//Imrpesión de la matriz
	//system ("cls");
	cout << "La matriz traspuesta es:" << endl << endl;
	for (i=0; i<col; i++){
		for (j=0; j<fil; j++){
			cout << matrixTraspuesta [i][j] << "\t";
		}
		cout << endl << endl;
	}
	return 0;
}
