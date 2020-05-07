#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

//Generador de ejemplos para el problema de encontrar el máximo y el mínimo.
//Simplemente, para rellenar el vector de tamaño n genera n enteros aleatorios entre 0 y INT.MAX_INT

// Si se quieren generar vectores distintos de diferente tamaño, basta modificar la semilla:


int main(int argc, char** argv){

	if (argc != 2 && argc != 3){
		cerr << "Formato: " << argv[0] << " <num_elem> [<semilla>]" << endl;
		return -1;
	}

	int n = atoi(argv[1]);
	
	int seed = 0;
	if(argc == 3){
		seed = atoi(argv[2]);
	}

	int * T = new int[n];
	assert(T);

	srand(seed);
	
	for (int j=0; j<n; j++) {
		T[j]=rand();
	}

	for (int j=0; j<n-1; j++){
		cout << T[j] << " ";
	}
	cout << T[n-1] << endl;

}