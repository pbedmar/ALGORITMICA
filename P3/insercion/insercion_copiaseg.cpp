#include<iostream>
#include<fstream>
#include<chrono>
#include<vector>
#include<math.h>
#include<errno.h>

using namespace std;

struct ciudad{
	int nodo, coord_x, coord_y;
};

double distanciaEuclideaCiudades(ciudad c1, ciudad c2)
{
	int c1x = c1.coord_x;
	int c2x = c2.coord_x;
	int c1y = c1.coord_y;
	int c2y = c2.coord_y;

	double distancia = sqrt(pow(c2x-c1x,2)+pow(c2y-c1y,2));
	return distancia;
}

void leerArchivo(string path, vector<ciudad> & v)
{
	ifstream f(path);

	if(!f.is_open()){
		cerr << "Error en la apertura del archivo"  << endl;
    	exit(-1);
	}

	string aux;
	for(int i=0;i<6;i++){
		getline(f,aux);
	}

	f >> aux;

	while(aux!="EOF"){

		ciudad ciudadInsertar;

		ciudadInsertar.nodo = stoi(aux);

		f >> aux;
		ciudadInsertar.coord_x = stoi(aux);

		f >> aux;
		ciudadInsertar.coord_y = stoi(aux);

		v.push_back(ciudadInsertar);

		f>>aux;
	}
}

void construirMatrizDistancias(vector<ciudad> v, vector<vector<int> > & m)
{
	for(int i=0;i<v.size();i++){
		for(int j=i;j<v.size();j++){
			m[i][j] = distanciaEuclideaCiudades(v[i],v[j]);
			m[j][i] = m[i][j];
		}
	}
}

int calcularCoste(vector<ciudad> v, vector<vector<int> > m){
	int coste = 0;

	for(int i=0;i<v.size()-1;i++){
		coste += m[v[i].nodo][v[i+1].nodo];
	}

	coste += m[v[0].nodo][v[v.size()-1].nodo ];

	return coste;
}

int main(int argc, char **argv){

	//Comprobación del número de parámetros
	if (argc != 2)
    {
    	cerr << "Formato: ./insercion <fichero_ciudades_.tsp"  << endl;
    	return -1;
    }

    vector<ciudad> ciudades;
    leerArchivo(argv[1],ciudades);

    vector<vector<int> > matrizDistancias(ciudades.size(), vector<int>(ciudades.size()));
    
    // for(vector<ciudad>::const_iterator it=ciudades.cbegin();it!=ciudades.cend();++it){
    // 	cout << (*it).nodo << " " << (*it).coord_x << " " << (*it).coord_y << endl;
    // }

    construirMatrizDistancias(ciudades,matrizDistancias);

 	//for(int i=0;i<10;i++){
 	//    	cout << endl;
	// 	for(int j=0;j<10;j++){
	// 		cout << matrizDistancias[i][j] << "\t";
	// 	}
	// }
	// cout << endl;

	int max_norte=0, max_este=0, max_oeste=ciudades[0].coord_y;
	ciudad c_norte, c_este, c_oeste;
	int posicion;

    for(vector<ciudad>::const_iterator it=ciudades.cbegin();it!=ciudades.cend();++it)
    {
    	if((*it).coord_y>max_norte){
    		max_norte = (*it).coord_y;
    		c_norte = (*it);
    	}
    	if((*it).coord_x>max_este){
    		max_este = (*it).coord_x;
    		c_este = (*it);
    	}
    	if((*it).coord_x<max_oeste){
    		max_oeste = (*it).coord_x;
    		c_oeste = (*it);
    	}
    }

    // cout << c_norte.nodo << " " << c_este.nodo << " " << c_oeste.nodo;
    // cout << endl;

    vector<ciudad> ciudades_visitadas;
    vector<ciudad> ciudades_por_visitar;

    for(int i=0;i<ciudades.size();i++){
    	if(ciudades[i].nodo!=c_norte.nodo&&ciudades[i].nodo!=c_oeste.nodo&&ciudades[i].nodo!=c_este.nodo){
    		ciudades_por_visitar.push_back(ciudades[i]);
    	}	
    }

 //    cout << endl << "Tamanio: " << ciudades_por_visitar.size() << endl;
	// for(vector<ciudad>::const_iterator it=ciudades_por_visitar.cbegin();it!=ciudades_por_visitar.cend();++it){
 //    	cout << (*it).nodo << " " << (*it).coord_x << " " << (*it).coord_y << endl;
 //    }


    ciudad minima_ciudad;
    int posicion_minima_visitadas;
    int posicion_minima_por_visitar;
    int coste;
    vector<ciudad> aux;

    ciudades_visitadas.push_back(c_norte);
    ciudades_visitadas.push_back(c_este);
    ciudades_visitadas.push_back(c_oeste);

    cout << "Tamanio ciudades_por_visitar: " << ciudades_por_visitar.size() << endl;

    while(!ciudades_por_visitar.empty()){
    	int minimo = 10000000;

    	for(int k=0;k<ciudades_por_visitar.size();k++){

    		for(int i=0;i<ciudades_visitadas.size();i++){

    			// cout << "..." << ciudades_visitadas[i].nodo;

    			aux = ciudades_visitadas;
    			ciudad nueva = ciudades_por_visitar[k];
    			//cout << "Coordenada nueva: " << nueva.nodo << " " << nueva.coord_x << " " << nueva.coord_y << endl;
    			aux.insert(aux.begin()+i,nueva);
    			coste = calcularCoste(aux,matrizDistancias);

    			if(coste < minimo){
    				minimo = coste;
    				minima_ciudad = ciudades_por_visitar[k];
    				posicion_minima_visitadas = i;
    				posicion_minima_por_visitar = k;
    			}

    		}

    		aux = ciudades_visitadas;
    		//aux.push_back(ciudades_por_visitar[k]);
    		coste = calcularCoste(aux,matrizDistancias);

			if(coste < minimo){
				minimo = coste;
				minima_ciudad = ciudades_por_visitar[k];
				posicion_minima_visitadas = aux.size()-1;
				posicion_minima_por_visitar = k;
			}

    	}
    	cout << "ehehehe";

    	//ciudades_visitadas.insert(ciudades_visitadas.begin()+posicion_minima_visitadas,minima_ciudad);
    	cout << endl << "MINIMA CIUDAD: " << minima_ciudad.nodo << endl;
    	//ciudades_visitadas.push_back(minima_ciudad);
    	ciudades_por_visitar.erase(ciudades_por_visitar.begin()+posicion_minima_por_visitar);

    }






















}