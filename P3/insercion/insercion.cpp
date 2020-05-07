#include<iostream>
#include<fstream>
#include<chrono>
#include<vector>
#include<math.h>
#include<errno.h>
using namespace std;

//Cada una de las ciudades por donde pasa el viajante. Nodo es su identificador y coord_x y coord_y indican la posición en el mapa.
struct ciudad{
	double nodo, coord_x, coord_y;
};

//Devuelve la distancia euclídea entre dos ciudades.
double distanciaEuclideaCiudades(ciudad & c1, ciudad & c2)
{
	double distancia = sqrt(pow((1.0)*c2.coord_x-c1.coord_x,2)+pow((1.0)*c2.coord_y-c1.coord_y,2));
	return distancia;
}

//Lee el archivo .tsp dado su path y almacena las ciudades que obtiene en un std::vector
void leerArchivo(string path, vector<ciudad> & v)
{
	ifstream f(path);

	if(!f.is_open()){
		cerr << "Error en la apertura del archivo"  << endl;
    	exit(-1);
	}

    //Leemos hasta encontrar el inicio de la sección de nodos
    string aux;
    do{
        f >> aux;
    } while (aux!="NODE_COORD_SECTION");

    f >> aux;

    //Leemos palabra por palabra hasta encontrar "EOF"
    //Almacenamos nodo, coord_x y coord_y de cada ciudad
	while(aux!="EOF"){

		ciudad ciudadInsertar;

		ciudadInsertar.nodo = stof(aux);

		f >> aux;
		ciudadInsertar.coord_x = stof(aux);

		f >> aux;
		ciudadInsertar.coord_y = stof(aux);

		v.push_back(ciudadInsertar);

		f>>aux;
	}
}

//Matriz cuadrada con dimensión equivalente al número de ciudades. En cada m[i][j] se almacena la distancia entre la ciudad i y j
void construirMatrizDistancias(vector<ciudad> & v, vector<vector<double> > & m)
{
	for(int i=0;i<v.size();i++){
		for(int j=i;j<v.size();j++){
			m[i][j] = distanciaEuclideaCiudades(v[i],v[j]);
			m[j][i] = m[i][j];
		}
	}
}

//Calcula el coste producido por recorrer las ciudades en el orden en que se encuentran en el vector v
//El coste es la suma total de distancia desde la ciudad inicial hasta que se vuelve a ella
double calcularCoste(vector<ciudad> & v, vector<vector<double> > & m){
	double coste = 0;

	for(int i=0;i<v.size()-1;i++){
		coste += m[v[i].nodo-1][v[i+1].nodo-1];
	}

	coste += m[v[0].nodo-1][v[v.size()-1].nodo-1];

	return coste;
}

int main(int argc, char **argv){

	//Comprobación del número de parámetros
	if (argc != 2)
    {
    	cerr << "Formato: ./insercion <fichero_ciudades_.tsp"  << endl;
    	return -1;
    }

    //Definición y carga de datos en el vector de ciudades y en la matriz de distancias
    vector<ciudad> ciudades;
    leerArchivo(argv[1],ciudades);
    vector<vector<double> > matrizDistancias(ciudades.size(), vector<double>(ciudades.size()));
    construirMatrizDistancias(ciudades,matrizDistancias);

    //Cálculo de las ciudades que se encuentran más al norte, este y oeste. A partir de estas tres ciudades se calcula el resto
	double max_norte=0, max_este=0, max_sur=ciudades[0].coord_x;
	ciudad c_norte, c_este, c_sur;

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
    	if((*it).coord_y<max_sur){
    		max_sur = (*it).coord_y;
    		c_sur = (*it);
    	}
    }

    //Creamos un vector con las ciudades ya recorridas y otro con las que faltan por recorrer
    vector<ciudad> ciudades_visitadas;
    vector<ciudad> ciudades_por_visitar;

    for(int i=0;i<ciudades.size();i++){
    	if(ciudades[i].nodo!=c_norte.nodo&&ciudades[i].nodo!=c_sur.nodo&&ciudades[i].nodo!=c_este.nodo){
    		ciudades_por_visitar.push_back(ciudades[i]);
    	}	
    }

    ciudad minima_ciudad;
    int posicion_minima_visitadas;
    int posicion_minima_por_visitar;
    double coste;
    vector<ciudad> aux;

    ciudades_visitadas.push_back(c_norte);
    ciudades_visitadas.push_back(c_este);
    ciudades_visitadas.push_back(c_sur);


    clock_t t_antes=clock();

    while(!ciudades_por_visitar.empty()){
        double minimo = 1000000;

    	for(int k=0;k<ciudades_por_visitar.size();k++){

    		for(int i=0;i<ciudades_visitadas.size();i++){

    			aux = ciudades_visitadas;
    			ciudad nueva = ciudades_por_visitar[k];
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
    		aux.push_back(ciudades_por_visitar[k]);
    		coste = calcularCoste(aux,matrizDistancias);


			if(coste < minimo){
				minimo = coste;
				minima_ciudad = ciudades_por_visitar[k];
				posicion_minima_visitadas = aux.size()-1;
				posicion_minima_por_visitar = k;
			}
    	}


    	ciudades_visitadas.insert(ciudades_visitadas.begin()+posicion_minima_visitadas,minima_ciudad);
    	ciudades_por_visitar.erase(ciudades_por_visitar.begin()+posicion_minima_por_visitar);


    }


    clock_t t_despues=clock();

    cout << endl << "Ciudades eficientes:" << endl;
    for(vector<ciudad>::const_iterator it=ciudades_visitadas.cbegin();it!=ciudades_visitadas.cend();++it){
     cout << (*it).nodo << " " << (*it).coord_x << " " << (*it).coord_y << endl;
    }

    cout << "Peso total: " << calcularCoste(ciudades_visitadas,matrizDistancias) << endl;

    cout << "  " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;
}