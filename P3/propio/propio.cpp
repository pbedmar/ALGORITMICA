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

void swap_vector(vector<ciudad> & v, int inicio, int fin){
    
    for(int i=inicio,k=fin; i<=fin/2;i++,k--){
        ciudad aux = v[i];
        v[i] = v[k];
        v[k] = aux;
    }
}

int main(int argc, char **argv){

    srand(time(NULL));

    //Comprobación del número de parámetros
    if (argc != 2)
    {
        cerr << "Formato: ./insercion <fichero_ciudades_.tsp"  << endl;
        return -1;
    }

    //Definición y carga de datos en el vector de ciudades y en la matriz de distancias
    vector<ciudad> ciudades_definitivas;
    leerArchivo(argv[1],ciudades_definitivas);
    vector<vector<double> > matrizDistancias(ciudades_definitivas.size(), vector<double>(ciudades_definitivas.size()));
    construirMatrizDistancias(ciudades_definitivas,matrizDistancias);

    vector<ciudad> ciudades_provisional(ciudades_definitivas);
    cout << ciudades_provisional.size() << endl;

    int contador = 0;
    double distancia;

    clock_t t_antes=clock();

    while(contador < 500){
        int coste_minimo = calcularCoste(ciudades_definitivas,matrizDistancias);
        for(int i=0; i<ciudades_definitivas.size(); i++){
            for(int j=i+1;j<ciudades_definitivas.size(); j++){
                swap_vector(ciudades_provisional, i, j);
                int coste_total = calcularCoste(ciudades_provisional,matrizDistancias);

                if(coste_total < coste_minimo){
                    ciudades_definitivas = ciudades_provisional;
                    coste_minimo = coste_total;
                    contador = 0;
                }
            }
        }
        contador++;
    }

    clock_t t_despues=clock();

    for(vector<ciudad>::const_iterator it=ciudades_definitivas.cbegin();it!=ciudades_definitivas.cend();++it){
     cout << (*it).nodo << " " << (*it).coord_x << " " << (*it).coord_y <<  endl;
    }

    cout << "Peso total: " << calcularCoste(ciudades_definitivas,matrizDistancias) << endl;

}