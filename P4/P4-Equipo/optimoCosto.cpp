#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

// Cada una de las ciudades está compuesta por un nodo(identificador) y 
// su posición dada por la coordenada x e y
struct ciudad{
    int nodo;
    double coord_x, coord_y;
};

//Devuelve la distancia euclídea entre dos ciudades dadas.
double distanciaEuclideaCiudades(ciudad & c1, ciudad & c2)
{
    return sqrt(pow((1.0)*c2.coord_x-c1.coord_x,2)+pow((1.0)*c2.coord_y-c1.coord_y,2));
}

void leerCiudades(string path, vector<ciudad>& ciudades)
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

    f >> aux;   // Primera ciudad de la lista
    
    ciudad ciudadAInsertar;
    // Leemos palabra por palabra hasta encontrar el fin de fichero(EOF)
    while(aux!="EOF"){
        ciudadAInsertar.nodo = stoi(aux);       // Identificador
        f >> aux;
        ciudadAInsertar.coord_x = stof(aux);    // Coordenada x
        f >> aux;   
        ciudadAInsertar.coord_y = stof(aux);    // Coordenada y

        ciudades.push_back(ciudadAInsertar);    // Insertamos ciudad

        f>>aux;     // Leer siguiente ciudad
    }
}


void leerCaminoOptimo(string path, vector<int>& caminoOptimo)
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
    } while (aux!="TOUR_SECTION");

    f >> aux;       // Leemos la primera coordenada(as)

    while(aux!="-1"){
        caminoOptimo.push_back(stoi(aux));
        f >> aux;
    }

    caminoOptimo.push_back(-1);     // Insertamos el -1 para tener un centinela
}


double calcularCostoOptimo(vector<ciudad>& ciudades, vector<int> caminoOptimo)
{
    double costo = 0.0;
    int nodo1, nodo2, j=0;
    nodo1 = caminoOptimo[j];
    nodo2 = caminoOptimo[j++];

    while(nodo1 != -1 && nodo2 != -1){
        costo += distanciaEuclideaCiudades(ciudades[nodo1-1], ciudades[nodo2-1]);   // Restamos uno ya que la ciudad 1 por ejemplo
                                                                                    // ocupa la posición 0 de ciudades
        nodo1=nodo2;                // Vamos desde el antiguo destino a la siguiente
        nodo2=caminoOptimo[j++];    // Pasar a la siguiente ciudad
    }

    // Sumar la distancia de ir desde la última ciudad a la primera
    costo += distanciaEuclideaCiudades(ciudades[caminoOptimo[0]-1], ciudades[caminoOptimo[caminoOptimo.size()-2]-1]);

    return costo;
}


int main(int argc, char** argv)
{
    if(argc<3){
        cerr << "Numero de argumentos incorrecto." << endl;
        cerr << "Ejemplo de uso:" << endl;
        cerr << "./optimoCosto <fichero_ciudades> <fichero_camino_optimo>" << endl;
        exit(-1);
    }

    vector<ciudad> ciudades;            // Contendrá las ciudades
    vector<int> caminoOptimo;           // Contendrá el camino óptimo

    leerCiudades(argv[1], ciudades);
    leerCaminoOptimo(argv[2], caminoOptimo);

    cout << "El costo del camino optimo es " << calcularCostoOptimo(ciudades, caminoOptimo) << endl << endl;
}