//g++ viajanteComercioCercania.cpp -o viajanteComercioCercania
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
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

	if(!fi.is_open()){
		cout << "Error al especificar el nombre del archivo" << endl;
		exit(1);
	}

	fi >> linea_inicial;
	fi >> num_ciudades; //contiene el numero de ciudades

	if(num_ciudades <= 0)
		exit(1);

	while(num_ciudades > 0){
		ciudad ciu;
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

void eliminaCiudad(vector<int> &ciudades, int numero){
	bool salir = false;
	auto borrar = ciudades.begin();
	auto i = ciudades.begin();

	for(i = ciudades.begin(); i != ciudades.end() && !salir; ++i){
		if(numero == (*i)){
			salir = true;
			borrar = i;
		}
	}
	ciudades.erase(borrar);
}


int main(int argc, char ** argv){
	vector<ciudad> vector_leido;

	int minimo_coste;

	if(!argc == 2){
		cout << "Error en el numero de argumentos" << endl;
		exit(1);
	}

	leeDatos(argv[1], vector_leido);

	vector<vector<int>> matriz_distancias(vector_leido.size(),
															  vector<int>(vector_leido.size()));

	calculaMatrizDistancias(vector_leido, matriz_distancias);

	//Hasta aquí hemos trabajado con el struct nodo, ahora trabajamos con enteros
	vector<int> ciudades_seleccionadas;
	vector<int> ciudades_candidatas;
	vector<int> ciudades_candidatas_copia;

	int por_donde_voy;


	for(int i = 0; i < vector_leido.size(); i++){
		ciudades_candidatas_copia.push_back(i);
	}

	int coste_plan;
	int minimo_coste_plan;
	vector<int> solucion;
	minimo_coste_plan = 9999999;

	tantes = high_resolution_clock::now();

	for(int i = 0; i < ciudades_candidatas_copia.size(); i++){
		ciudades_candidatas = ciudades_candidatas_copia;
		ciudades_seleccionadas.clear();

		ciudades_seleccionadas.push_back(ciudades_candidatas[i]);

		eliminaCiudad(ciudades_candidatas, ciudades_candidatas[i]);

		coste_plan = 0;

		while(!ciudades_candidatas.empty()){
			int minimo_coste = 999999;
			int vecino_mas_proximo = ciudades_candidatas[0];
			por_donde_voy = ciudades_seleccionadas.back();
			int ciudad_primera;
			int ciudad_ultima;

			for(int i = 0; i < ciudades_candidatas.size(); i++){
				int ciudad = ciudades_candidatas[i];
				int	coste = matriz_distancias[por_donde_voy][ciudad];

					if(coste < minimo_coste){
						vecino_mas_proximo = ciudad;
						minimo_coste = coste;
					}
			}

			coste_plan += minimo_coste;

			ciudades_seleccionadas.push_back(vecino_mas_proximo);
			eliminaCiudad(ciudades_candidatas, vecino_mas_proximo);
		}

		int ciudad_primera = ciudades_seleccionadas.front();
		int ciudad_ultima = ciudades_seleccionadas.back();

		coste_plan += matriz_distancias[ciudad_primera][ciudad_ultima];

		if(coste_plan < minimo_coste_plan){
 			minimo_coste_plan = coste_plan;
			solucion = ciudades_seleccionadas;
		}
	}

	tdespues = high_resolution_clock::now();

  	transcurrido = duration_cast<duration<double>>(tdespues - tantes);

  	cout << transcurrido.count() << endl;

	return 0;
}
