#include<iostream>
#include<fstream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<math.h>
#include<errno.h>
using namespace std;

//Cada una de las ciudades por donde pasa el viajante. Nodo es su identificador y coord_x y coord_y indican la posición en el mapa.
struct ciudad{
    double nodo, coord_x, coord_y;
};

vector<ciudad> ciudades;

//Devuelve la distancia euclídea entre dos ciudades dadas.
double distanciaEuclideaCiudades(ciudad & c1, ciudad & c2)
{
    double distancia = sqrt(pow((1.0)*c2.coord_x-c1.coord_x,2)+pow((1.0)*c2.coord_y-c1.coord_y,2));
    return distancia;
}

//Lee el archivo .tsp dado su path y almacena las ciudades que obtiene en un std::vector
//Para que la lectura se haga correctamente las ciudades deberan estar entre la etiqueta
// 'NODE_CORRD_SECTION' al inicio y 'EOF' al final.
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

int costeMin(ciudad cinicial, vector<ciudad> & c, vector<vector<double> > & mDistancias){
    if(c.size()>0){
        int coste_min=1000000, coste_actual;
        for(int i=0;i<c.size();i++){
            vector<ciudad> c_aux(c);
            c_aux.erase(c_aux.begin()+i);
            coste_actual = costeMin(c[i],c_aux,mDistancias) + distanciaEuclideaCiudades(cinicial,c[i]);
            if(coste_actual<coste_min){
                coste_min = coste_actual;

            }  
        }
        return coste_min; 
    } else {
        return distanciaEuclideaCiudades(cinicial,ciudades[0]);  
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
    leerArchivo(argv[1],ciudades);

    vector<vector<double> > matrizDistancias(ciudades.size(), vector<double>(ciudades.size()));
    construirMatrizDistancias(ciudades,matrizDistancias);

    vector<ciudad> c_aux(ciudades);
    c_aux.erase(c_aux.begin());

    cout << "Coste total: " << costeMin(ciudades[0],c_aux,matrizDistancias) << endl;

}
