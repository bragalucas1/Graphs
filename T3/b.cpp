/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Kruskal foi reaproveitado do problema A - vide explicação da implementação lá.
Dúvidas presenciais com o professor tiradas no dia 23/11/2023.
Pessoas com as quais discuti sobre este exercício:
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

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
	int peso;
	Edge(int v = -1, int w = -1, int peso = 0) : v(v), w(w), peso(peso) { }
};

bool operator <(const Edge &i,const Edge &j) {
	return i.peso<j.peso;
}

int calculate(const int d1, const int d2) {
    int resposta = 0;
    int finalResult = 0;
    if (d1 == d2) {
        return 0;
    }

    if (d2 > d1) {
        int firstPart = d2 - d1;
        if(firstPart <= 5){
            finalResult = firstPart;
        }
        else{
            finalResult = 10-firstPart;
        }
        return finalResult;
    }

    if(d1 - d2 <=5){
        resposta = d1 - d2;
    }
    else{
        resposta = 10 - (d1-d2);
    }
    return resposta;
}

int calculateNumberOfRolls(string &s1, string &s2){
    int numberRolls = 0;
    for(int i = 0; i < 4; i++){
        numberRolls += calculate(static_cast<int>(s1[i]), static_cast<int>(s2[i]));
    }
    return numberRolls;
}

//TODO: SALVAR STRING QUE JA FUI
int mineKruskal(vector<Edge> &arestas, const int &sizeOfVertex){
    //Pega as arestas ordenadas da mais barata para a mais cara
    sort(arestas.begin(), arestas.end()); //Não precisa passar um functor pois já existe o operador de comparação inerente.
    int  peso = 0;
    int nArestas = 0;
    UnionFind uf;
    uf.createSet(sizeOfVertex);

    for(int i = 0; i < arestas.size(); i++){
        if(!uf.isSameSet(arestas[i].v, arestas[i].w)){ //estão em componentes diferentes e não gerará ciclo
            nArestas++;
            peso += arestas[i].peso;
            if(nArestas == sizeOfVertex-1) break; //ja chegamos a uma arvore

            uf.mergeSets(arestas[i].v, arestas[i].w);
        }
    }
    return peso;
}


// Um botão mágico JUMP pode transformar os dígitos em qualquer uma das teclas desbloqueadas sem rolar.
void resolve(const int nStrings, vector<string> &vec, map<string,int> &map){
    int result = 0;
    string index = "0000";
    string menorD;
    vector<string> alreadySeen;
    vector<Edge> arestas;
    int least = INT_MAX;

    //Partindo para a senha mais curta. Done.
    for(int i = 0; i < nStrings; i++){
        result = calculateNumberOfRolls(index, vec[i]);         
        if (result < least) {
            least = result;
            menorD = vec[i];
        }
    }

    for(int i = 0; i < nStrings; i++){
        for(int j = i+1; j < nStrings; j++){
            Edge e;
            e.v = map[vec[i]];
            e.w = map[vec[j]];
            e.peso = calculateNumberOfRolls(vec[i], vec[j]);
            arestas.push_back(e);
        }
    }
    int pesoAgm = mineKruskal(arestas, nStrings);
    cout << pesoAgm+least << endl;              
}

int main(){
    int testCase;
    cin >> testCase;

    for(int i = 0; i < testCase; i++){
        int nStrings;
        map<string, int> map;
        cin >> nStrings;
        vector<string> t;
        for(int j = 0; j < nStrings; j++){
            string entry;
            cin >> entry;
            int idMap = map.size();
            map[entry] = idMap;
            t.push_back(entry);
        }
        resolve(nStrings, t, map);
        t.clear();
        map.clear();
    }

    return 0;
}