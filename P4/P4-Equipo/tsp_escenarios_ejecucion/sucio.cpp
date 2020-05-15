double f(ciudad ciudad1, vector<ciudad> S, vector<vector<double>> matrizDistancias)
{
    double coste_actual; 
    double coste_min = numeric_limits<double>::max();
    int cardinalidad= S.size();
    bool para;

    if(S.size() == 0){
        return matrizDistancias[ciudad1.nodo-1][0];
    }
    else
    {
        for(int j=0; j < cardinalidad; j++){
            vector<ciudad> S_modificado = S;
            para = false;
            //Borrar elemento j del conjunto de ciudades a comparar
            vector<ciudad>::const_iterator it;
            for(it = S_modificado.begin(); it !=S_modificado.end() && !para; ++it){
                if((*it).nodo == S[j].nodo){
                    S_modificado.erase(it);
                    para = true;
                }
            }
            coste_actual = matrizDistancias[ciudad1.nodo-1][S[j].nodo-1] + f(S[j], S_modificado, matrizDistancias);
            if(coste_actual < coste_min){
                coste_min = coste_actual;

            }
        }
    }
    return coste_min;
}