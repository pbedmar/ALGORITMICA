/* 
  Fichero: tsp-PD.cpp
  Autores:  Joaquín García Venegas
            Joaquín Alejandro España Sánchez
            Pedro Bedmar López
            Alejandro Escalona García
  Fecha: 14/05/20
  Compilación: g++ tsp-PD.cpp -o tsp-PD
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include <limits>
#include <algorithm>

using namespace std;

// Representa a una ciudad
// Nodo es su identificador y coord_x y coord_y indican la posición en el mapa
struct ciudad{
    int nodo; 
    double coord_x, coord_y;
};


//Devuelve la distancia euclídea entre dos ciudades 
double distanciaEuclideaCiudades(const ciudad & c1, const ciudad & c2)
{
    double distancia = sqrt(pow((1.0)*c2.coord_x-c1.coord_x,2)+pow((1.0)*c2.coord_y-c1.coord_y,2));
    return distancia;
}


// Lee el archivo .tsp dado su path y almacena las ciudades que obtiene en un std::vector
// Para que la lectura se haga correctamente las ciudades deberan estar entre la etiqueta
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

        ciudadInsertar.nodo = stoi(aux);    // Ientificador(nodo)
        f >> aux;
        ciudadInsertar.coord_x = stof(aux); // Coordenada x
        f >> aux;
        ciudadInsertar.coord_y = stof(aux); // Coordenada y

        v.push_back(ciudadInsertar);        // Insertamos la ciudad

        f>>aux;
    }
}


// Matriz cuadrada con dimensión equivalente al número de ciudades
// En cada m[i][j] se almacena la distancia entre la ciudad i y j
void construirMatrizDistancias(const vector<ciudad>& v, vector<vector<double> >& m)
{
    for(int i=0;i<v.size();i++){
        for(int j=i;j<v.size();j++){
            m[i][j] = distanciaEuclideaCiudades(v[i],v[j]);
            m[j][i] = m[i][j];      // La matriz de distancias es simétrica
        }
    }
}


//Funcion para comprobar si una ciudad esta contenida en un subconjunto
bool estaContenida(int &nodoOrigen, const vector<int>& subconjunto)
{
    bool contenido = false;
    for(int i=0; i<subconjunto.size() && !contenido; i++){
        if(nodoOrigen == subconjunto[i]-1){
            contenido = true;
        } 
    }
    return contenido;
}

//Funcion para obtener el numero de columna de un subconjunto
int ColumnaMatrizConSubconjunto(const vector<vector<int>>& subconjuntos, const vector<int>& sub_a_buscar)
{
    bool encontrado = false;
    int pos = -1;

    for(int i=0; i<subconjuntos.size() && !encontrado; i++){
        if(subconjuntos[i] == sub_a_buscar){
            encontrado = true;
            pos = i;
        }
    }

    return pos;
}


// Función que calcula cual es la ciudad, de un conjunto de ciudades S (vector con sus nodos), con la que se 
// obtiene el mínimo coste desde una ciudad origen
pair<double, int> f(int nodoOrigen, const vector<int>& S, const vector<vector<double>>& matrizDistancias, const vector< vector<pair<double, int> >>& matrizDinamica, const vector< vector<int> >& subconjuntos)
{
    double coste_actual = 0; 
    double coste_min = numeric_limits<double>::max();
    int nodo_minimo = 0;

    // L(i,1)
    if(S.size() == 0){
        return make_pair(matrizDistancias[nodoOrigen][0], nodoOrigen+1);
    }
    // Devolver infinito si esta contenida
    else if(estaContenida(nodoOrigen, S)){
        return make_pair(numeric_limits<double>::max(), -1);
    }
    // Devolver la distancia minima: L(i,j) + f(j, P-{j})
    // L es la matriz distancias, y P un subconjunto de ciudades
    else{
        vector<int> aux;
        vector<int>::iterator it;
        int contador = 0;

        // Cogemos un subconjunto y vamos eliminando elementos en distintas posiciones
        for(int i=0; i<S.size(); i++, contador++){
            aux=S;
            it = aux.begin();

            for(int j=0; j<contador; j++)
                ++it;

            aux.erase(it);

            // Coste de: L(i,j) + f(j, P-{j})
            coste_actual = matrizDistancias[nodoOrigen][S[i]-1]; //L(i,j)
            coste_actual += matrizDinamica[S[i]-1][ColumnaMatrizConSubconjunto(subconjuntos,aux)].first;//f(j, P-{j})
      
            if(coste_actual < coste_min){
                coste_min = coste_actual;
                nodo_minimo = S[i];
            }
        }
    }
    return make_pair(coste_min, nodo_minimo);
}


// Funcion para generar todos los subconjuntos posibles con los numeros desde inicio a N
void generaSubconjuntos(int inicio, vector<bool> & conjunto,vector<vector<int> >& subconjuntos, int N)
{
	if(inicio == N)
	{
        vector<int> sub;
		for(int i = 0; i < N; i++)
		{
            if(conjunto[i] == true){
                sub.push_back(i+1);
            }
        }
        subconjuntos.push_back(sub);
	}
	else
	{
		conjunto[inicio] = true;
		generaSubconjuntos(inicio + 1, conjunto, subconjuntos, N);
		conjunto[inicio] = false; 
		generaSubconjuntos(inicio + 1, conjunto, subconjuntos, N);
	}
}


// Funcion que ordena por tamaño de los vectores, y si son del mismo tamaño, 
// los ordena por su contenido
bool ordenaSubconjuntos(vector<int> a, vector<int> b){
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

// Funcion para obtener los subconjuntos formados con los numeros desde 1 a nº de ciudades
vector<vector<int>> obtenerSubconjuntos(int n_ciudades)
{
    // Vector para almacenar los subconjuntos
    vector< vector<int> > subconjuntos;
    
    // Vector de booleanos (para que funcione la funcion que genera subconjuntos)
    vector<bool> bools(pow(2, n_ciudades));
    
    // Llamar a la función que forma los subconjuntos
    generaSubconjuntos(1, bools, subconjuntos, n_ciudades);

    // Ordenarlos correctamente
    sort(subconjuntos.begin(), subconjuntos.end(), ordenaSubconjuntos);

    // Devolver los subconjuntos
    return subconjuntos;
}


// Funcion para obtener la matriz con los costes optimos
vector<vector<pair<double, int>>> obtenerMatrizDinamica(int n_ciudades, vector<vector<double>> matrizDistancias, vector< vector<int> > subconjuntos)
{

    // Matriz a rellenar
    vector<vector<pair<double, int>>> matrizDinamica(n_ciudades, vector<pair<double, int>>(subconjuntos.size()));

    // Vamos rellenando la matriz por columnas, y por cada columna por filas
    for(int col=0; col<subconjuntos.size(); col++){
        cout << "Ahora va por la columna " << col << endl;
        for(int fil=0; fil < n_ciudades; fil++){
                // De la primera fila rellenamos todo con infinito menos la ultima columna (donde estara la solucion) y la primera
                if(fil==0 && col != (subconjuntos.size()-1) && col!=0) 
                    matrizDinamica[fil][col].first = numeric_limits<double>::max();
                else
                    matrizDinamica[fil][col] = f(fil, subconjuntos[col], matrizDistancias, matrizDinamica, subconjuntos);
        }
    }
    
    return matrizDinamica;
}


// Función para obtener el camino una vez generada la matriz dinamica
vector<int> calcularCamino(vector< vector<pair<double, int>> > matrizDinamica, vector< vector<int> > subconjuntos)
{
    int tam = subconjuntos.size(), col;
    int fila = matrizDinamica[0][tam-1].second;
    int columna;
    bool encontrado;

    vector<int> camino(1,1);    // Siempre se empieza el camino por la ciudad 1 (ciudad origen)
    camino.push_back(matrizDinamica[0][tam-1].second);  // Añadimos la segunda ciudad a visitar
    
    vector<int> subc = subconjuntos[tam-1]; // Subconjunto con n-1 ciudades al inicio del algoritmo (ya que la 1 esta visitada ya)
                                            // A este conjunto le iremos quitando las ciudades que visitemos
    
    while(!subc.empty()){       // Mientras queden ciudades por visitar
        columna = -1;
        encontrado = false;

        // Eliminamos el elemento del conjunto dado por el nodo de la ciudad (nº de fila de la matriz + 1) donde se obtenia el costo minimo del subconjunto
        for(vector<int>::iterator it= subc.begin(); it != subc.end() && !encontrado; ++it){
            if((*it) == fila){
                subc.erase(it);
                encontrado = true;
            }
        }
        
        if(!subc.empty()){
            // Buscamos el indice de columna de la matriz (coincide con el vector de subconjuntos) 
            // con el subconjunto resultante
            for(int i=0; i<subconjuntos.size() && columna==-1; i++){
                if(subc == subconjuntos[i]){
                    columna = i;
                }
            } 

            fila = matrizDinamica[fila-1][columna].second;     // Obtenemos el nodo de la ciudad donde se consigue el minimo con ese subconjunto
            camino.push_back(fila);                            // Añadimos la ciudad al camino
        }
    }

    return camino;
}


int main(int argc, char **argv)
{
    //Comprobación del número de parámetros
    if (argc != 2)
    {
        cerr << "Formato: ./tsp-PD <fichero_ciudades_.tsp"  << endl;
        return -1;
    }

    vector<ciudad> ciudades;        // Vector que contendrá las ciudades a visitar 

    // Carga de datos en el vector de ciudades
    leerArchivo(argv[1],ciudades);

    // Creación de la matriz de distancias
    vector<vector<double> > matrizDistancias(ciudades.size(), vector<double>(ciudades.size()));
    construirMatrizDistancias(ciudades,matrizDistancias);

    clock_t t_antes=clock();
        // Obtener los subconjuntos
        vector<vector<int>> subconjuntos = obtenerSubconjuntos(ciudades.size());
        // Obtener la matriz dinámica
        vector<vector<pair<double, int>> > matriz = obtenerMatrizDinamica(ciudades.size(), matrizDistancias, subconjuntos);
        // Obtener el camino
        vector<int> camino = calcularCamino(matriz, subconjuntos);
    clock_t t_despues=clock();


//SALIDA
    
    // //Imprimir matriz dinamica
    // cout << "La matriz dinamica es: " << endl;
    // for(int i=0; i < matriz.size(); i++){
    //     for(int j=0; j<matriz[i].size(); j++)
    //         cout << matriz[i][j].first << "(" << matriz[i][j].second << ") \t ";
    //     cout << endl;
        
    
   // Imprimir el tiempo que consume el algoritmo
    cout << "Tiempo: " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << " s" << endl;

    // Imprimir el numero de ciudades del camino
    cout << camino.size() << endl; 
    
    // Imprimir el camino (nodo  coord_x    coord_y)
    for(int i=0; i < camino.size(); i++)
        cout << ciudades[camino[i]-1].nodo << " " << ciudades[camino[i]-1].coord_x << " " << ciudades[camino[i]-1].coord_y <<  endl;

    // Imprimir el coste del camino
    cout << "Coste optimo: " << matriz[0][subconjuntos.size()-1].first << endl;
}