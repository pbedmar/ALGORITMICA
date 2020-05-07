#include <iostream>
using namespace std;
#include <cstdlib>
#include <cassert>
#include <errno.h>
#include <list>

int main(int argc, char * argv[]){

/*--------------------------*/
// ENTRADA INICIAL DE DATOS

if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <tamaño_grafo>" << endl;
      return -1;
    }

int n = atoi(argv[1]);
/*--------------------------*/

//INICIALIZACION DE VARIABLES

int u=0; //etiqueta del nodo
int matriz[n][n];
int matriz2[n][n]; 

list <int> vertice;//Subconjunto solución

int minimo;
double px,py;
int datos[n*2];
int distancias[n];
int contadore,contadord,contadordis;

/*--------------------------*/
// Rellenamos matriz a ceros

for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
              matriz[i][j] = 0;
    }
}

/*--------------------------*/
// Entrada de datos (Guarda en vector todas las coordenadas)

/* contadore = 0;
contadord = 0;
while (contador<n){

	cin >> px >> py;

datos[contadord] = px;
datos[contadord+1] = py;

cout << "contador: " << contadore << endl;
contadord = contadord + 2;
contadore++;
}

for (int i=0; i<n*2; i++)
	cout << datos[i] << " ";

	cout << "\n\n";
*/

/*--------------------------------------------------*/
//Matriz rellenada a distancias (no funciona)

/*contadordis = 0;

for (int i=0; i<n; i++){
	for (int j=2; j<n; j++){

 	distancias[contadordis] = sqrt(pow(datos[j]-datos[i],2) + pow(datos[j+1]-datos[i+1],2));
	contadordis++;

	}
}

for (int i=0; i<n*2; i++)
	cout << distancias[i] << " ";

*/

// EJEMPLO PARA EL CODIGO
/*----------------*/
matriz[0][1]=2;
matriz[0][2]=8;
matriz[0][3]=3;
matriz[0][4]=6;
/*----------------*/
matriz[1][0]=2;
matriz[1][2]=4;
matriz[1][3]=8;
matriz[1][4]=8;
/*----------------*/
matriz[2][0]=8;
matriz[2][1]=4;
matriz[2][3]=7;
matriz[2][4]=3;
/*----------------*/
matriz[3][0]=3;
matriz[3][1]=8;
matriz[3][2]=7;
matriz[3][4]=3;
/*----------------*/
matriz[4][0]=6;
matriz[4][1]=8;
matriz[4][2]=3;
matriz[4][3]=3;
/*----------------*/


for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
              matriz2[i][j] = 0;
    }
}

matriz2[0][1]=2;
matriz2[0][2]=8;
matriz2[0][3]=3;
matriz2[0][4]=6;

/*-----------------*/
// Matriz rellenada

cout << "\nMATRIZ RELLENADA: \n";
for (int a=0;a<n;a++){
        for (int b=0;b<n;b++){
            cout << " " << matriz[a][b] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

/*-----------------*/

bool aumento;			//Limitar a una ejecución por fila hasta encontrar primer minimo
int contador;			//contador1 = posición del primer elemento distinto de cero
int contador2;			//contador2 = en ultima iteracción, ponemos a cero y sumamos distancia minima
int val1,val2; 
int contador_bucle = 0;
int suma_distancia = 0;		//Distancia minimal


for(int i=0; contador_bucle < n-1;){

	contador_bucle++;
	aumento = true;
	contador2 = 0;

	for(int j=0; j<n; j++){
		if (aumento){
			contador = 0;

			while (matriz[i][contador]==0){			//Calculamos primer elemento !=0 que será el primer minimo
				contador++;
			}

			minimo = matriz[i][contador]; 
			val1 = i;
			val2 = contador;
			aumento = false;
		}
	
		contador2++;
		if(matriz[i][j]!=0){					//Calculamos minimo real de la fila distinto de cero
			if(matriz[i][j] < minimo){
				minimo = matriz[i][j]; 
				val1 = i;
				val2 = j;
			}
		}
		
		if (contador2 == n){					//Sumar distancias y poner a cero matriz	
			suma_distancia = suma_distancia + minimo;
			i = val2;
			vertice.push_back(val1);

			 for(int j=0; j<n; j++){

                  		  matriz[j][val1]=0;
                   		  matriz[j][val2]=0; 
			}

		}
		
		if (contador_bucle==(n-1) and j==n-1){			//Si es ultimo nodo, añadir distancia hacia el primer nodo
			vertice.push_back(val2);
			suma_distancia = suma_distancia + matriz2[0][val2];

		}
	}
}

cout << "\nMATRIZ MODIFICADA: \n";

for (int a=0;a<n;a++){
        for (int b=0;b<n;b++){
            cout << " " << matriz[a][b] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";

cout << "- Resultado: [";

while (!vertice.empty()){		
	u=vertice.front();
		cout << u << " ";
		vertice.pop_front();
}

cout << "]\n";
cout << "- DISTANCIA: " << suma_distancia << "\n\n";

return 0;

}
