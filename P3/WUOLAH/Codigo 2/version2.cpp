#include <iostream>
using namespace std;
#include <cstdlib>
#include <cassert>
#include <errno.h>
#include <list>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>

void leer_orden(string & nombre, vector<int> & V){
    ifstream datos;
    string s;
    pair<double,double> p;
    int n, act;
  
    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    V.reserve(n);
    int i=0;
    while (i<n) {
        datos >> act;
	V.push_back(act);
	i++;
      }
       
    datos.close();
    }
   else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
 }

void leer_puntos(string & nombre, map<int, pair<double, double> > & M, int &n){
    ifstream datos;
    string s;
    pair<double,double> p;
    int act;
    
    
    datos.open(nombre.c_str());
    if (datos.is_open()) {
    datos >> s; // Leo "dimension:"
    datos >> n;
    int i=0;
    while (i<n) {
        datos >> act >> p.first >> p.second;
	M[act] = p;
	i++;
      }
       
    datos.close();
    }
   else { 
      cout << "Error de Lectura en " << nombre << endl;
    }
 }

class CLParser
{
public:

    CLParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CLParser(){}

    string get_arg(int i);
    string get_arg(string s);

private:

    int argc;
    vector<string> argv;

    bool switches_on;
    map<string,string> switch_map;
};

CLParser::CLParser(int argc_, char * argv_[],bool switches_on_)
{
    argc=argc_;
    argv.resize(argc);
    copy(argv_,argv_+argc,argv.begin());
    switches_on=switches_on_;

    //map the switches to the actual
    //arguments if necessary
    if (switches_on)
    {
        vector<string>::iterator it1,it2;
        it1=argv.begin();
        it2=it1+1;

        while (true)
        {
            if (it1==argv.end()) break;
            if (it2==argv.end()) break;

            if ((*it1)[0]=='-')
                switch_map[*it1]=*(it2);

            it1++;
            it2++;
        }
    }
}

string CLParser::get_arg(int i)
{
    if (i>=0&&i<argc)
        return argv[i];

    return "";
}

string CLParser::get_arg(string s)
{
    if (!switches_on) return "";

    if (switch_map.find(s)!=switch_map.end())
        return switch_map[s];

    return "";
}

int main(int argc, char * argv[])
{
  
  map<int, pair<double, double> >  m;
  vector<int> V;
  string fp,fok;
	int n;
   if (argc == 1) {
     cout << "Error Formato:  tsp puntos orden_correcto" << endl;
     exit(1);
   }
    
	CLParser cmd_line(argc,argv,false);

    fp = cmd_line.get_arg(1);
    leer_puntos(fp,m,n);
    fok = cmd_line.get_arg(2);

    leer_orden(fok,V);
	
	double distancia[n][n],recorrido[n][n];
	int v;
	map<int, pair<double, double> >::iterator it1, it2;
	int i,j;
	for(it1=m.begin(),i=0;it1!=m.end();++it1,i++){
		for(it2=it1, j=0; it2!=m.end();++it2,j++){
			if(i!=j){			
				v=sqrt(pow((((*it2).second).first-((*it1.second).first),2.0)+pow((((*it2).second).second-((*it1.second).second),2.0));
				distancia[i][j]=v;
				distancia[j][i]=v;
			}
			else{
				distancia[i][j]=0;
			}
		}
	}
	
	set<int> ciudades;
	int cnorte=0,ceste=0,coeste=0;
	int vnorte=-1000,veste=-1000,voeste=1000;
	int distancia_total=0,dist_local,pos,aux;
	vector<int> camino_final,v_local;
	vector<int>::iterator it_v,it_aux;

	for(it1=m.begin();it1!=m.end(); ++it1){
		if(((*it1).second).second>vnorte ){
			vnorte = ((*it1).second).second;
			cnorte = (*it1).first;
		}
	}
	ciudades.insert(cnorte); camino_final.push_back(cnorte);
	for (it1=m.begin();it1!=m.end();++it1){
		if(((*it1).second).first>veste && (*it1).first != cnorte){
			veste = ((*it1).second).first;
			ceste = (*it1).first;
		}
   	}
	ciudades.insert(ceste);
	camino_final.push_back(ceste);
	for (it1=m.begin();it1!=m.end();++it1){
		if(((*it1).second).first<voeste && (*it1).first != cnorte && (*it1).first != ceste){
			voeste = ((*it1).second).first;
			coeste = (*it1).first;
		}
   	}
	ciudades.insert(coeste); 
	camino_final.push_back(coeste);
	
	for (it1=m.begin();it1!=m.end();++it1){
		if(((*it1).second).first<voeste && (*it1).first != cnorte && (*it1).first != ceste){
			voeste = ((*it1).second).first;
			coeste = (*it1).first;
		}
   	}
	ciudades.insert(coeste); 
	camino_final.push_back(coeste);
		
	int tamloc=n-3,ciudad;
	while(tamloc>0){
		for (it1=m.begin();it1!=m.end();++it1){
			dist_local=1000;
			v_local.clear();
			v_local.insert(v_local.begin(),camino_final.begin(),camino_final.end());
				
			for(j=0;j<camino_final.size();j++){
				if(ciudades.find((*it1).first)==ciudades.end()){
					for(i=0,it_v=v_local.begin();i<=j;i++,++it_v){}
						v_local.insert(it_v,(*it1).first);
							aux= distancia_recorrida(n,distancia,v_local);
							if(aux<dist_local){
								ciudad=(*it1).first;
								dist_local=aux;	
								pos = j;					
							}				
				}

				v_local.clear();
				v_local.insert(v_local.begin(),camino_final.begin(),camino_final.end());
					
			}
		}
		for(i=0,it_aux=camino_final.begin();i<=pos;i++,++it_aux){}

		ciudades.insert(ciudad);
		camino_final.insert(it_aux,ciudad);	
			
		tamloc--;
	}
	for(i=0;i<camino_final.size();i++){
		cout<<camino_final[i]<<" ";
	}
	cout << endl;
	cout << distancia_recorrida(n,distancia,camino_final);
	cout << endl;



}

