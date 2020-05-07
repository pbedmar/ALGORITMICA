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

int calculaCosteCamino(vector<ciudad> & v, vector<vector<int> > & matriz_distancias){
	int coste_total = 0;

	for (int i = 0; i < (v.size()-1); i++){
		coste_total += matriz_distancias[(v[i].num_ciudad)-1][(v[i+1].num_ciudad)-1];
	}

	coste_total += matriz_distancias[(v[(v.size()-1)].num_ciudad)-1][(v[0].num_ciudad) - 1];

	return coste_total;
}

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

void eliminaCiudad(vector<ciudad> &ciudades, int numero){
	bool salir = false;
	auto i = ciudades.begin();
	auto borrar = ciudades.begin();

	for(i = ciudades.begin(); i != ciudades.end() && !salir; ++i){
		if(numero == (*i).num_ciudad){
			salir = true;
			borrar = i;
		}
	}

	ciudades.erase(borrar);
}


int main(int argc, char ** argv){
	vector<ciudad> vector_ciudades;
	vector<ciudad> vector_ciudades_candidatas;
	vector<ciudad> vector_ciudades_seleccionadas;

	if(argc != 2){
		cout << "Error en el numero de argumentos" << endl;
		exit(1);
	}

	leeDatos(argv[1], vector_ciudades);	// Obtenemos el vector de ciudades

	vector_ciudades_candidatas = vector_ciudades; // Inicializamos el vector de ciudades candidatas

	// Inicializamos la matriz de distancias
	vector<vector<int>> matriz_distancias(vector_ciudades.size(),	vector<int>(vector_ciudades.size()));
	calculaMatrizDistancias(vector_ciudades, matriz_distancias);

	int mayor_x = -1, mayor_y = -1, menor_y = 10000000;
	ciudad norte,este,sur;

	// Elegimos las ciudades que se encuentren más al este, norte y sur.

	for (int i = 0; i < vector_ciudades.size(); i++){
		if (vector_ciudades[i].coordenada_x > mayor_x){ // ciudad mas el este
			mayor_x = vector_ciudades[i].coordenada_x;
			este = vector_ciudades[i];
		}

		if (vector_ciudades[i].coordenada_y > mayor_y){ // ciudad mas al norte
			mayor_y = vector_ciudades[i].coordenada_y;
			norte = vector_ciudades[i];
		}

		if (vector_ciudades[i].coordenada_y < menor_y){ // ciudad mas al sur
			menor_y = vector_ciudades[i].coordenada_y;
			sur = vector_ciudades[i];
		}
	}

	// Las añadimos al vector de ciudades seleccionadas

	vector_ciudades_seleccionadas.push_back(norte);
	vector_ciudades_seleccionadas.push_back(este);
	vector_ciudades_seleccionadas.push_back(sur);

	// Las quitamos del vector de ciudades candidatas

	eliminaCiudad(vector_ciudades_candidatas, norte.num_ciudad);
	eliminaCiudad(vector_ciudades_candidatas, este.num_ciudad);
	eliminaCiudad(vector_ciudades_candidatas, sur.num_ciudad);

	int coste, coste_minimo = 10000000, coste_minimo_total = 10000000;
	int donde_insertar1;
	int donde_insertar2;
	ciudad cual_insertar;
	int contador = 0;
	vector<ciudad> prueba;
	tantes = high_resolution_clock::now();

	while (!vector_ciudades_candidatas.empty()){ // Mientras nos queden ciudades por seleccionar
		coste_minimo_total = 10000000;
		for (auto i=vector_ciudades_candidatas.begin(); i != vector_ciudades_candidatas.end(); i++){ // Recorremos las ciudades restantes
			coste_minimo = 10000000;																 // por incluir
			contador = 0;

			// Probamos a incluir la ciudad i al final de las seleccionadas
			prueba = vector_ciudades_seleccionadas;
			prueba.push_back(*i);
			coste = calculaCosteCamino(prueba, matriz_distancias);
			if (coste < coste_minimo){ // Si es coste de incluirla es menor que la mínima hasta el momento, lo registramos
				coste_minimo = coste;
				donde_insertar1 = vector_ciudades_seleccionadas.size();
			}

			// Probamos el resto de las posiciones donde insertar la ciudad i
			for (auto j=vector_ciudades_seleccionadas.begin(); j != vector_ciudades_seleccionadas.end(); j++){
				prueba = vector_ciudades_seleccionadas;
				prueba.insert(prueba.begin()+contador, *i);
				coste = calculaCosteCamino(prueba, matriz_distancias);
				if (coste < coste_minimo){ // Nos quedamos con la posicion donde sea mínimo el coste de insertarla
					coste_minimo = coste;
					donde_insertar1 = contador;
				}
				contador++;
			}			
			// Si insertando la ciudad i en la posicion donde_insertar1 causamos un incremento mínimo del circuito, lo registramos
			if (coste_minimo < coste_minimo_total){
			 	coste_minimo_total = coste_minimo;
				cual_insertar = *i;
				donde_insertar2 = donde_insertar1;
			}
		}

		// Insertamos la ciudad cual_insertar en la posicion donde_insertar2 de tal forma que nos cause un incremento mínimo en el circuito
		if (donde_insertar2 == vector_ciudades_seleccionadas.size()){
			vector_ciudades_seleccionadas.push_back(cual_insertar);
		} else {
			vector_ciudades_seleccionadas.insert(vector_ciudades_seleccionadas.begin() + donde_insertar2, cual_insertar);
		}
		eliminaCiudad(vector_ciudades_candidatas, cual_insertar.num_ciudad); // Eliminamos la ciudad seleccionada del vector de candidatas
	}


	tdespues = high_resolution_clock::now();

  	transcurrido = duration_cast<duration<double>>(tdespues - tantes);

  	for(vector<ciudad>::const_iterator it=vector_ciudades_seleccionadas.cbegin();it!=vector_ciudades_seleccionadas.cend();++it){
     cout << (*it).num_ciudad << " " << (*it).coordenada_x << " " << (*it).coordenada_y << endl;
    }

	return 0;
}
