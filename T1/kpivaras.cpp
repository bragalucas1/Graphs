/*
README
Fontes de consulta: https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c/
Material adaptado do professor sobre BFS Pilha. Professor, reitero que, assisti as aulas gravadas do PER, refiz todo o fluxo, anotei em minhas anotações
no caderno e adaptei todo o código para resolver, porém ainda assim ficou semelhante. Não encontrei outra forma de fazer, visto que já havia visto sua implementação e, dessa forma
ja possuia a ideia na cabeça.
Pessoas com as quais discuti sobre este exercício:
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

void learnedBFS(const vector<list<int>> &adj, 
				vector<bool> &discoveredVertex, 
				vector<int> &ordem, const int v) {
	queue<int> fila; fila.push(v);
	discoveredVertex[v] = true;	
	ordem[v] = 1;

	while(!fila.empty()) {
		int vertexToExplore = fila.front(); 
		fila.pop();		

		for(int i:adj[vertexToExplore]) {
			if (!discoveredVertex[i]) {
				discoveredVertex[i] = true;
				ordem[i] = ordem[vertexToExplore]+1;
				fila.push(i);	
			}		
		}
	}
}

void printTree(const vector<list<int>> &adj){
	for (int i = 0; i < adj.size(); i++) {
		cout << "adj[" << i+1 << "]: ";
		for (const int &element : adj[i]) {
			cout << element+1 << " ";
		}
		cout << endl;
	}
}

int main() {
	int kPiv = 0;
	cin >> kPiv;
	vector<list<int>> adj(kPiv);
	vector<bool> visited(kPiv, false);
	vector<int> ordem(kPiv, -1);
	vector<int> isRoot;

	for (int i = 0; i < kPiv; i++) {
		int u;
		cin >> u;
		if(u != -1){
			adj[u-1].push_back(i);
			adj[i].push_back(u-1);
		}
		else{
			isRoot.push_back(i);
		}
	}

	for(int i = 0; i < isRoot.size(); i ++){
		learnedBFS(adj, visited, ordem, isRoot[i]);
	}

	int maxValue = *max_element(ordem.begin(), ordem.end());
	cout << maxValue << endl;

	return 0;
}
