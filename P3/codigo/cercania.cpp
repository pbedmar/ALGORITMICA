/*
Realizado por:
Alejandro Escalona García
Pedro Bedmar Lopez
Joaquin Garcia Venegas
Joaquin Alejandro España Sanchez
*/
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

int main(int argc, char **argv){

    srand(time(NULL));

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

    //Creamos un vector con las ciudades ya recorridas y otro con las que faltan por recorrer
    vector<ciudad> ciudades_visitadas;
    vector<ciudad> ciudades_por_visitar;

    ciudad minima_ciudad;
    int posicion_minima;
    double distancia;
    int coste_total_minimo=10000000;
    vector<ciudad> ciudades_visitadas_minimas;

    clock_t t_antes=clock();


    for(int i = 0; i < ciudades.size(); i++){

        ciudades_visitadas.clear();
        ciudades_por_visitar.clear();
        int coste_total;
        ciudades_visitadas.push_back(ciudades[i]); //Insertamos la ciudad seleccionada para esta iteración.

        for(int j=0;j<ciudades.size();j++){  
            if(j!=i){
                ciudades_por_visitar.push_back(ciudades[j]); //Borramos la ciudad que ha sido seleccionada para esta iteración.
            }
        }

        while(!ciudades_por_visitar.empty()){
            double distancia_minima = 10000000;

            for(int k=0;k<ciudades_por_visitar.size();k++){
                distancia = distanciaEuclideaCiudades(ciudades_por_visitar[k],ciudades_visitadas.back());

                if(distancia<distancia_minima){ //Si la distancia es la menor, significa que es la ciudad más cercana y por lo tanto la escogemos.
                    distancia_minima = distancia;
                    minima_ciudad = ciudades_por_visitar[k];
                    posicion_minima = k;
                }
            }
            

            ciudades_visitadas.push_back(minima_ciudad); //Insertamos la ciudad más cercana.
            ciudades_por_visitar.erase(ciudades_por_visitar.begin()+posicion_minima); //Borramos la ciudad más cercana que ya ha sido insertada.

        }

        coste_total = calcularCoste(ciudades_visitadas,matrizDistancias); 
        if(coste_total<coste_total_minimo){ //Comprobamos si este recorrido iniciado en la ciudad i, es el minimo entre todos los recorridos.
            ciudades_visitadas_minimas = ciudades_visitadas;
            coste_total_minimo = coste_total;
        }

    }


    clock_t t_despues=clock();

    for(vector<ciudad>::const_iterator it=ciudades_visitadas_minimas.cbegin();it!=ciudades_visitadas_minimas.cend();++it){
     cout << (*it).nodo << " " << (*it).coord_x << " " << (*it).coord_y <<  endl;
    }

    cout << "Tiempo de ejecucion: "<<((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

    cout << "Peso total: " << calcularCoste(ciudades_visitadas_minimas,matrizDistancias) << endl;

}
