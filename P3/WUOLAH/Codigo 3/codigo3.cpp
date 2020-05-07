#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
//#include <chrono>

//using namespace std::chrono;

//high_resolution_clock::time_point tantes, tdespues;
//duration<double> transcurrido;

int main(){

int n;
cin >> n;

int matriz[n][n]; //Matriz
int v1, v2;

int vertice[n]; //Subconjunto solución
int t = 0; //Contador que aumentaremos en 2 para meter los datos en vértice

/*--------------------------------------------------*/
//Rellenamos matriz a ceros

for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
              matriz[i][j] = 0;
    }
}

/*while ((v1!=-1 and v2!=-1) and (v1<n or v2<n)){

      cin >> v1 >> v2;
      matriz[v1][v2]=1;
}*/

//EJEMPLO PARA RELLENAR LA MATRIZ
/*----------------*/
matriz[0][0]=0;
matriz[0][1]=2;
matriz[0][2]=8;
matriz[0][3]=3;
matriz[0][4]=6;
/*----------------*/
matriz[1][0]=2;
matriz[1][1]=0;
matriz[1][2]=4;
matriz[1][3]=8;
matriz[1][4]=8;
/*----------------*/
matriz[2][0]=8;
matriz[2][1]=4;
matriz[2][2]=0;
matriz[2][3]=7;
matriz[2][4]=3;
/*----------------*/
matriz[3][0]=3;
matriz[3][1]=8;
matriz[3][2]=7;
matriz[3][3]=0;
matriz[3][4]=3;
/*----------------*/
matriz[4][0]=6;
matriz[4][1]=8;
matriz[4][2]=3;
matriz[4][3]=3;
matriz[4][4]=0;
/*----------------*/
/*--------------------------------------------------*/

//Matriz rellenada

cout << "\nMATRIZ RELLENADA: \n";
for (int a=0;a<n;a++){
        for (int b=0;b<n;b++){
            cout << " " << matriz[a][b] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";

/*--------------------------------------------------*/

/* Cogemos un arista y sus dos vértices. Posteriormente los quitaremos y volveremos a elegir una arista de manera aleatoria */

//tantes = high_resolution_clock::now();

int ultima_ciudad = n-1;//Metemos la última ciudad que introduciremos al final
int distancia, suma_distancia;

for(int x=0; x<n; x++){
    for(int y=0; y<n; y++){
        if(matriz[x][y]!=0){ //Si encuentra la ciudad con una distancia a otra distinta de 0
           
	    //Mete los dos vértices subconjunto solución
	    vertice[t]=x;
            vertice[t+1]=y;
	    t = t + 2;            
	    
	    //SUMA DE LAS DISTANCIAS
            distancia = matriz[x][y];
	    suma_distancia = suma_distancia + distancia;

	    for(int d=0; d<n; d++){ //Borrar las conexiones con esos vértices(FILAS)
                    matriz[x][d]=0;
                    matriz[y][d]=0;        
            }

            //Borramos las Columnas
            for(int d=0; d<n; d++){
                    matriz[d][x]=0;
                    matriz[d][y]=0;        
            }
        }
    }
}

vertice[t]= ultima_ciudad; //ULTIMA CIUDAD AÑADIDA

//tdespues = high_resolution_clock::now();
 
// Matriz resultante

/*cout << "MATRIZ MODIFICADA: \n";

for (int a=0;a<n;a++){
        for (int b=0;b<n;b++){
            cout << " " << matriz[a][b] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
*/

cout << "Resultado: [";

for(int g=0; g<=t; g++)
    cout << vertice[g] << " ";

cout << "]\n";

cout <<" Distancia: "<< suma_distancia<< endl;



//transcurrido = duration_cast<duration<double>>(tdespues - tantes);
//cout << n << "    " << transcurrido.count() << endl;

return 0;

}
