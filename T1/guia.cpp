    /*
    README
    Fontes de consulta: Algoritmo tubo.cpp para retirada do código de Tarjan.
    Slide sobre articulações.
    Buscas em sites gerais sobre hash_map e uso de map em c++.
    Código wordTransformation.cpp para entender mais do uso de map e indices para vertices com "label".
    Duvidas gerais com o professor via e-mail e presencial.
    Pessoas com as quais discuti sobre este exercício:
    */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;


//Codigo adaptado da implementacao do livro Competitive Programming
void tarjan(int u, const vector<vector<int> > &adj, vector<int> &dfsParent, vector<int> &dfsNum,
					 vector<int> &dfsLow, vector<bool> &isArticulation,vector<pair<int,int> > &bridges, 
						int &dfsCount, int &rootChildren, int dfsRoot) {
	dfsLow[u] = dfsNum[u] = ++dfsCount; // dfsLow[u] <= dfsNum[u]
	for(int v:adj[u]) {
		//vertices nao descobertos tem tempo de descoberto (dfsNum) 0 
		if (dfsNum[v] == 0) { 
				dfsParent[v] = u; //pai de v e' u (v foi descoberto por u)
			if (u == dfsRoot) //caso especial... precisamos contar quantas vezes descobrimos vertices a partir da raiz para descobrir se raiz e' articulacao...
				rootChildren++; 

			tarjan(v,adj,dfsParent,dfsNum,dfsLow,isArticulation,bridges,dfsCount,rootChildren,dfsRoot);

			if (dfsLow[v] >= dfsNum[u]) //apos visitar v recursivamente, conseguimos chegar em um vertice em v ou antes passando por u? (sem voltar pela aresta v,u)
				isArticulation[u] = true; // store this information first
			if (dfsLow[v] > dfsNum[u]) // ponte?
				bridges.push_back(make_pair(u,v));
			dfsLow[u] = min(dfsLow[u], dfsLow[v]); // update dfsLow[u]
		}
		else if (v != dfsParent[u]) //cheguei de volta em um vertice ja descoberto... se nao passei pela aresta v,u de volta --> ciclo...
			dfsLow[u] = min(dfsLow[u], dfsNum[v]); //atualize dfsLow...
	}
}
void tarjan(const vector<vector<int> > &adj, 
						vector<bool> &isArticulation,
                        vector<pair<int,int> > &bridges) {
	int nv = adj.size();
	isArticulation = vector<bool>(nv,false);
	bridges.resize(0);

	vector<int> dfsParent(nv,-1);
	vector<int> dfsLow(nv,0);
	vector<int> dfsNum(nv,0);	
	int dfsCount = 0;

	//para multiplos CCs ...
	for(int i=0;i<nv;i++) {
		if(dfsNum[i]==0) {
			int rootChildren = 0;  //resete para cada CC!!
			tarjan(i, adj, dfsParent, dfsNum , dfsLow, isArticulation, bridges, dfsCount, rootChildren, i);
			isArticulation[i] = rootChildren>1;
		}
	}
}

/*Print auxiliar.*/
void printAdj(const vector<string> &indexToName,  const map<string,int> &nameToIndex,  vector<vector<int>> &adj){
    for (int i = 0; i < nameToIndex.size(); i++) {
        string placeName = indexToName[i];
        cout << "Adjacências de " << placeName << " (" << i << "): ";

        for (int j = 0; j < adj[i].size(); j++) {
                int neighborIndex = adj[i][j];
                string neighborName = indexToName[neighborIndex];
                cout << neighborName << " (" << neighborIndex << ") ";

                if (j < adj[i].size() - 1) {
                    cout << " - ";
            }
        }
    cout << endl;
    }
}

int main() {
    int N;
    int numTest = 0;
    bool first = true;
    while (cin >> N && N > 0) {
        map<string, int> nameToIndex;
        vector<string> indexToName(N);
        
        for (int i = 0; i < N; i++) {
            string placeName;
            cin >> placeName;
            int id = nameToIndex.size();
            nameToIndex[placeName] = id;
            indexToName[id] = placeName;
        }

        int R;
        cin >> R;   

        int size = nameToIndex.size();
        vector<vector<int>> adj(size, vector<int>());

        for(int i = 0; i < R; i++){
            string edge1, edge2;
            cin >> edge1 >> edge2;
            adj[nameToIndex[edge1]].push_back(nameToIndex[edge2]);
            adj[nameToIndex[edge2]].push_back(nameToIndex[edge1]);
        }
        numTest++;

       /*Os 2 primeiros vetores abaixo são nativos da função Tarjan e o subsequente seria para retirar as articulações propriamente ditas, de modo a facilitar
       a ordenação - requerida pelas saidas - e manipulação apenas dessas.*/
       vector<bool> isArticulation;
       vector<pair<int,int>> bridges;
       vector<string> articulationsResult;
       
       //Chamada da função principal.
       tarjan(adj, isArticulation, bridges);
       //---------------------------
       
       for(int i = 0; i < isArticulation.size(); i++){
            if(isArticulation[i]){
                articulationsResult.push_back(indexToName[i]);
            }
       } 

       sort(articulationsResult.begin(), articulationsResult.end());
       if(!first) cout << "\n";

       cout << "City map #" << numTest << ": " << articulationsResult.size() << " camera(s) found\n";
       for(auto &i: articulationsResult){
            cout << i << endl;
       }
    
	   first = false;
    }

    return 0;
}
