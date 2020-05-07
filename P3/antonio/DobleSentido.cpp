#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits.h>
#include <chrono>
using namespace std::chrono;



high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;


using namespace std;

struct ciudad{
	int num_ciudad;
	double coordenada_x;
	double coordenada_y;
};

//Función que lee los datos de las ciudades de un fichero y las almacena
//en un vector
void leeDatos(char * nombre_fichero, vector<ciudad> & vector_ciudades){
	ifstream fi(nombre_fichero);
	string linea_inicial;
	int num_ciudades;

	if(!fi){
		cout << "Error al especificar el nombre del archivo" << endl;
		exit(1);
	}

	fi >> linea_inicial;
	fi >> num_ciudades; //contiene el numero de ciudades

	if(num_ciudades <= 0)
		exit(1);

	ciudad ciu;
	while(num_ciudades > 0){
		fi >> ciu.num_ciudad;
		fi >> ciu.coordenada_x;
		fi >> ciu.coordenada_y;

		num_ciudades--;
		vector_ciudades.push_back(ciu);
	}

	fi.close();
}

//Funcion que calcula la distancia entre dos ciudades
int calculaDistancia(ciudad c1, ciudad c2){
	double distancia = -1;


	distancia = sqrt( 1.0*pow((c2.coordenada_x - c1.coordenada_x), 2)
				      + 1.0*pow((c2.coordenada_y - c1.coordenada_y), 2) );

	return round(distancia);
}

//Función que calcula la matriz de distancias
void calculaMatrizDistancias( vector<ciudad> & ciudades,
														vector<vector<int> > & matriz_distancias ){

	for(int i = 0; i < ciudades.size(); i++){
		for(int j = i; j < ciudades.size(); j++){
			if(i != j)
				matriz_distancias[i][j] =	matriz_distancias[j][i] = calculaDistancia(ciudades[i],ciudades[j]);

			else
				matriz_distancias[i][j] = 0;
		}
	}
}

int main (int argc, char ** argv)
{
	// Número de argumentos correcto
	if(!argc == 2){
		cout << "Error en el numero de argumentos" << endl;
		exit(-1);
	}

	vector<ciudad> vector_leido;

	 // Inicialización de datos //
	leeDatos(argv[1], vector_leido);
	vector<vector<int>> matriz_distancias(vector_leido.size(),
						    vector<int>(vector_leido.size()));
	calculaMatrizDistancias(vector_leido, matriz_distancias);

	vector<ciudad> candidatos (vector_leido), solucion, final;
	vector<ciudad>::iterator ciudades = vector_leido.begin(), c, minima;
	// Fin inicializacion estructuras de datos //

	int tour_minimo = INT_MAX;
	int ciudad_origen = 0;

	// Explicación del Algoritmo:
 	// Por cada ciudad como origen, desarrollaremos el algoritmo del vecino
  	// más cercano pero considerando ambas partes de nuestra solucion parcial.
  	// Es decir: Se agrega como ciudad siguiente aquella más cercana, (ya sea
  	// en la parte delantera o trasera de nuestro tour) que aún no haya sido visitada
tantes = high_resolution_clock::now();
	while (ciudades != vector_leido.end()){	// Recorremos ciudades

		solucion.push_back (candidatos[ciudad_origen]);
		candidatos.erase(candidatos.begin()+ciudad_origen);	

		ciudad actual, ciudad_min;
		int dist_minima = INT_MAX, distancia = 0, total = 0;
		bool inserta_ultimo = true;

		while (!candidatos.empty()){	// Aún me quedan candidatos

			actual = solucion.back();	// Extremo parte trasera
			c = candidatos.begin();
			dist_minima = INT_MAX;

			while (c != candidatos.end()){	// Recorremos resto de no visitadas

				distancia = matriz_distancias[actual.num_ciudad -1][c->num_ciudad -1];

				if (distancia < dist_minima){
					dist_minima = distancia;
					ciudad_min = *c;
					minima = c;
					inserta_ultimo = true;
				}
				++c;
			}
			// Volvemos a repetir lo mismo (Pero ahora por la otra parte)
			actual = *solucion.begin();	// Extremo parte delantera
			c = candidatos.begin();

			while (c != candidatos.end()){	// Recorremos resto de no visitadas

				distancia = matriz_distancias[actual.num_ciudad -1][c->num_ciudad -1];

				if (distancia < dist_minima){
					dist_minima = distancia;
					ciudad_min = *c;
					minima = c;
					inserta_ultimo = false;
				}
				++c;
			}
			// Dependiendo del menor coste (insertar parte principio o final)
			if(inserta_ultimo)
				solucion.push_back (ciudad_min);	// Ya está añadida, pasamos a otra
			else
				solucion.insert(solucion.begin(), ciudad_min);

			candidatos.erase(minima);
			total += dist_minima;

		}// while (!candidatos.empty())

		ciudad primera = solucion.front();
		ciudad ultima = solucion.back();

		// Distancia para cerrar el circuito
		distancia = matriz_distancias[primera.num_ciudad -1][ultima.num_ciudad -1];
		total+=distancia;

		if (total < tour_minimo){	// Minimo tour hasta ahora
			tour_minimo = total;
			final = solucion;
		}

		candidatos = vector_leido;	// Volvemos a rellenar los candidatos
		solucion.clear(); 			// Vaciamos nuestra parcial solución

		++ciudades;					// Siguiente ciudad a considerar como origen
		ciudad_origen++;

	}// while (ciudades != vector_leido.end())
		tdespues = high_resolution_clock::now();

  	transcurrido = duration_cast<duration<double>>(tdespues - tantes);

  	cout << transcurrido.count() << endl;
	}
