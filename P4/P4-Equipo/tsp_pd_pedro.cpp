#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include <limits>
#include <algorithm>

using namespace std;

//Cada una de las ciudades por donde pasa el viajante. Nodo es su identificador y coord_x y coord_y indican la posición en el mapa.
struct ciudad{
    int nodo; 
    double coord_x, coord_y;
};


struct casillaDinamica{
    double valor;
    int posMinimo;
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

        ciudadInsertar.nodo = stoi(aux);
        f >> aux;
        ciudadInsertar.coord_x = stof(aux);
        f >> aux;
        ciudadInsertar.coord_y = stof(aux);

        v.push_back(ciudadInsertar);

        f>>aux;
    }
}

//Matriz cuadrada con dimensión equivalente al número de ciudades. En cada m[i][j] se almacena la distancia entre la ciudad i y j
void  construirMatrizDistancias(vector<ciudad> & v, vector<vector<double> > & m)
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

bool estaContenida(int &nodoOrigen, vector<int>& ciudades)
{
    bool contenido = false;
    for(int i=0; i<ciudades.size() && !contenido; i++){
        if(nodoOrigen == ciudades[i]-1){
            contenido = true;
        } 
    }
    
    return contenido;
}

// Función que calcula cual es la ciudad de un conjunto de ciduades S  (vector con sus nodos) con la que se 
// tiene el mínimo coste desde una ciudad origen
double f(int nodoOrigen, vector<int> S, vector<vector<double>> matrizDistancias, int& nodo_minimo)
{
    double coste_actual = 0; 
    double coste_min = numeric_limits<double>::max();
    
    //L(i,1)
    if(S.size() == 0){
        nodo_minimo = nodoOrigen +1;
        return matrizDistancias[nodoOrigen][0];
    }
    //Devolver infinito si esta contenida
    else if(estaContenida(nodoOrigen, S)){
        return numeric_limits<double>::max();
    }
    //Devolver la distancia minima
    else{
        vector<int> aux;
        vector<int>::iterator it;
        int contador = 0;
        nodo_minimo = 0;

        //Cogemos un subconjunto y vamos eliminando elementos en distintas posiciones
        for(int i=0; i<S.size(); i++, contador++){
            aux=S;
            it = aux.begin();

            for(int j=0; j<contador; j++)
                ++it;

            aux.erase(it);

            coste_actual = matrizDistancias[nodoOrigen][S[i]-1] + f(S[i]-1, aux, matrizDistancias, nodo_minimo);


            if(coste_actual < coste_min){
                coste_min = coste_actual;
                nodo_minimo = S[i]; // (*it) -1 ; Estaba mal porque (*it) - 1 tendría subconjuntos de 0..max_subconjuntos
            }
        }
    }
    return coste_min;
}

//Funcion para obtener todos los subconjuntos posibles
void generaSubconjuntos(int k, vector<bool> & my_set,vector<vector<int> >& subconjuntos, int N)
{
	if(k == N)
	{
        vector<int> sub;
		// shows the subset
		for(int i = 0; i < N; i++)
		{
            if(my_set[i] == true){
                sub.push_back(i+1);
            }
        }
        subconjuntos.push_back(sub);
	}
	else
	{
		my_set[k] = true;
		generaSubconjuntos(k + 1, my_set, subconjuntos, N);
		my_set[k] = false; 
		generaSubconjuntos(k + 1, my_set, subconjuntos, N);
	}
}

//Funcion que ordena por tamaño de los vectores
bool ComparaTamanios(vector<int> a, vector<int> b){
    if(a.size() < b.size())
        return true;
    else if(a.size()==b.size()){
        for(int i =0; i < a.size(); i++){
            if(a[i] < b[i])
                return true;
            else if(a[i] > b[i])
                return false;
        }       
    }

    return false;
}

//Funcion para obtener la matriz con los costes optimos
vector<vector<casillaDinamica>> obtenerMatrizDinamica(vector<ciudad> ciudades, vector<vector<double>> matrizDistancias, vector< vector<int> > subconjuntos)
{

//Matriz a rellenar
    vector<vector<casillaDinamica>> matrizDinamica(ciudades.size(), vector<casillaDinamica>(subconjuntos.size()));

    //Vamos rellenando la matriz por columnas, y por cada columna por filas
    for(int col=0; col<subconjuntos.size(); col++){
        for(int fil=0; fil < ciudades.size(); fil++){
                //De la primera fila rellenamos todo con inf menos la ultima columna y la primera
                if(fil==0 && col != (subconjuntos.size()-1) && col!=0) 
                    matrizDinamica[fil][col].valor = numeric_limits<double>::max();
                else
                    matrizDinamica[fil][col].valor = f(fil, subconjuntos[col], matrizDistancias, matrizDinamica[fil][col].posMinimo);
        }
    }
    
    return matrizDinamica;
}


vector<int> calcularCamino(vector< vector<casillaDinamica> > matrizDinamica, vector< vector<int> > subconjuntos)
{
    vector<int> camino(1,1); //Añadimos la 1
    int tam = subconjuntos.size(), col;
    int fila = matrizDinamica[0][tam-1].posMinimo -1;
    camino.push_back(fila);
    int columna;
    bool encontrado;
    vector<int> subc = subconjuntos[tam-1]; //Lo igualamos al ultimo subconjunto
    
    while(!subc.empty()){
        columna = -1;
        encontrado = false;

        //Eliminamos el elemento del conjunto dado por la fila
        for(vector<int>::iterator it= subc.begin(); it != subc.end() && !encontrado; ++it){
            if((*it) == fila){
                subc.erase(it);
                encontrado = true;
            }
        }
        
        if(!subc.empty()){
            //Buscamos el indice de columna de la matriz (coincide con el vector de subconjuntos) 
            //con el subconjunto resultante
            for(int i=0; i<subconjuntos.size() && columna==-1; i++){
                if(subc == subconjuntos[i]){
                    columna = i;
                }
            } 

            fila = matrizDinamica[fila-1][columna].posMinimo;     // Guardamos la ciudad
            camino.push_back(fila);                             // Añadimos la ciudad al camino
        }
    }


    return camino;
}

int main(int argc, char **argv){

    //Comprobación del número de parámetros
    if (argc != 2)
    {
        cerr << "Formato: ./tsp-PD <fichero_ciudades_.tsp"  << endl;
        return -1;
    }

    //Definición y carga de datos en el vector de ciudades y en la matriz de distancias
    leerArchivo(argv[1],ciudades);

    vector<vector<double> > matrizDistancias(ciudades.size(), vector<double>(ciudades.size()));
    construirMatrizDistancias(ciudades,matrizDistancias);

/*
    vector<ciudad> c_aux(ciudades);     // Vector de ciudades auxiliar
    c_aux.erase(c_aux.begin());         // Borramos la primera ciudad de las ciudaddes
    vector<int> ruta(10);
    int contador=0;

    double coste=f(ciudades[0], ciudades, matrizDistancias);

    
    cout << "Matriz distancias: " << endl;
    for(int i=0; i<matrizDistancias.size(); i++){
        for(int j=0; j<matrizDistancias.size(); j++)
            cout << matrizDistancias[i][j] << "\t" ;
        cout << endl;
    }
    
*/

    //Obtener los subconjuntos
    vector< vector<int> > subconjuntos;
    
    // vector de booleanos (para que funcione la funcion que genera subconjuntos)
    vector<bool> booleanos(pow(2, ciudades.size()));
    
    // Llamar a la función que forma los subconjuntos
    generaSubconjuntos(1, booleanos, subconjuntos, ciudades.size());

    sort(subconjuntos.begin(), subconjuntos.end(), ComparaTamanios);


    // for(int i=0; i < subconjuntos.size(); i++){
    //     cout << "{ " ;
    //     for(int j=0; j<subconjuntos[i].size(); j++)
    //         cout << subconjuntos[i][j] << " ";
    //     cout << " }  ";
    // }
    // cout << endl;


    vector<vector<casillaDinamica> > matriz = obtenerMatrizDinamica(ciudades, matrizDistancias, subconjuntos);
    
    vector<int> camino = calcularCamino(matriz, subconjuntos);


    cout << "El camino óptimo es: ";
    for(int i=0; i<camino.size(); i++){
        cout << camino[i] << "--> ";
    }
    cout << endl;

    if(matriz.size() < 5){
        cout << "La matriz dinamica es: " << endl;
        for(int i=0; i < matriz.size(); i++){
            for(int j=0; j<matriz[i].size(); j++)
                cout << matriz[i][j].valor << "(" << matriz[i][j].posMinimo << ") \t ";
            cout << endl;
        }
    }
    
    cout << "Casilla con coste optimo: " << matriz[0][subconjuntos.size()-1].valor  << "(" << matriz[0][subconjuntos.size()-1].posMinimo << ") \t " <<endl;

}

