/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Kruskal foi implementado escutando a aula do dia - reforço, escutando - 2022-02-18 e analisando o pseudocódigo do Slide
disponibilizado no Drive da disciplina.
Pessoas com as quais discuti sobre este exercício:
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class UnionFind {
	private:
		vector<int> representante;
	public:
		void createSet(int tam) {
			representante.resize(tam);
			for(int i=0;i<tam;i++)
				representante[i] = i;
		}
		//Retorna o representante do conjunto que contem
		//o elemento "elemento"
		int findSet(int elemento) {
			if (representante[elemento]==elemento) 
				return elemento;
			//Compressao do caminho...
			representante[elemento] = findSet(representante[elemento]);
			return representante[elemento];
		}
		void mergeSets(int i,int j) {
			representante[ findSet(i) ] = findSet(j);
		}
		bool isSameSet(int i,int j) {
			return (findSet(i)==findSet(j));
		}

};

struct Edge 
{
	int v, w;
	long long peso;
	Edge(int v = -1, int w = -1, long long peso = 0) : v(v), w(w), peso(peso) { }
};

bool operator <(const Edge &i,const Edge &j) {
	return i.peso<j.peso;
}

// int calculateOddFatoration(long long peso){
//     return __builtin_ctzll(peso)+1;
// }

int calculateOddFatoration(const vector<long long> &peso){
    int exp = 0;
    for(int i = 0; i < peso.size(); i++){
        exp += __builtin_ctzll(peso[i]);
    }
    return exp+1;
}

void mineKruskal(vector<Edge> &arestas, const int &sizeOfVertex, UnionFind &uf){
    //Pega as arestas ordenadas da mais barata para a mais cara
    sort(arestas.begin(), arestas.end()); //Não precisa passar um functor pois já existe o operador de comparação inerente.
    long long peso = 1;
    int nArestas = 0;
    uf.createSet(sizeOfVertex);
    vector<long long> pesoVec;

    for(int i = 0; i < arestas.size(); i++){
        if(!uf.isSameSet(arestas[i].v, arestas[i].w)){ //estão em componentes diferentes e não gerará ciclo
            nArestas++;
            peso = arestas[i].peso;
            pesoVec.push_back(peso);

            if(nArestas == sizeOfVertex-1) break; //ja chegamos a uma arvore

            uf.mergeSets(arestas[i].v, arestas[i].w);
        }
    }
    cout << calculateOddFatoration(pesoVec) << endl;
}


// A DTI decidiu reconectar todos os computadores/switches, porém, 
// quer gastar o mínimo possível de modo que haja pelo menos uma rota entre qualquer par de equipamentos.
// Seu objetivo será calcular o custo mínimo para reestabelecer a conexão de toda a UFV. Como o valor final poderá ser astronômico, 
// por enquanto vamos querer saber apenas quantos divisores tal custo possui.
int main(){
    int t, n, m;
    cin >> t;
    vector<Edge> arestas;
    UnionFind uf;
    for(int i = 0; i < t; i++){
        cin >> n >> m;
        for(int j = 0; j < m; j++){
            int a, b;
            long long c;
            cin >> a >> b >> c; a--; b--;
            Edge e;
            e.v = a;
            e.w = b;
            e.peso = c;
            arestas.push_back(e);
        }
        mineKruskal(arestas, n, uf);
        arestas.clear();
    }

    // for(Edge &e: arestas){
    //     cout << e.v << " " << e.w << " " << e.peso << endl;
    // }

    return 0;
}
