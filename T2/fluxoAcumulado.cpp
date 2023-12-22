#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
vector<int> numEntradas;
vector<int> fluxoDoVertice;


vector<vector<int>> converterVetorEmMatriz(const int n, vector<int> &fluxoDoVertice){
    vector<vector<int>> matriz(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = fluxoDoVertice[i * n + j];
        }
    }
    return matriz;
}

void limitanteMenosUm(const int n) {
    vector<vector<int>> matrizDeFluxo = converterVetorEmMatriz(n, fluxoDoVertice);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrizDeFluxo[i][j] << " ";
        }
        cout << endl;
    }
}

void limitanteMenosDois() {
    long int somaTotal = 0;
    for(auto valor:fluxoDoVertice) somaTotal += valor;
    cout << somaTotal << endl;
}



void limitanteInteiro(const int limitante, const int n) {
    cout << "P1" << endl;
    cout << n << " " << n << endl;

    for(int i = 0; i < fluxoDoVertice.size(); i++) {
        if(fluxoDoVertice[i] >= limitante) cout << "1 ";
        else cout << "0 ";

        if((i+1)%n==0) cout << "\n";
    }
}

void calculaFluxo(const vector<vector<int>> &lista, const int n) {
    fluxoDoVertice.clear();
    for(int i = 0; i < n; i++) fluxoDoVertice.push_back(1);

    queue<int> verticesAProcessar;
    for(int i = 0; i < numEntradas.size(); i++)
        if(numEntradas[i] == 0) verticesAProcessar.push(i);
    
    int verticeAtual;
    while(!verticesAProcessar.empty()) {
        verticeAtual = verticesAProcessar.front();
        verticesAProcessar.pop();
        
        for(auto vizinho:lista[verticeAtual]) {
            fluxoDoVertice[vizinho] += fluxoDoVertice[verticeAtual];
            numEntradas[vizinho]--;
            if(numEntradas[vizinho] == 0) verticesAProcessar.push(vizinho);
        }
    }

}

int retornarVizinho(const vector<vector<int>> &matriz, const int i, const int j, const int n) {
    if(matriz[i][j] == 1) // se for 1 retorna diagonal superior esquerda
        if (i > 0 && j < n - 1) return ((i - 1) * n + (j - 1));
    
    if(matriz[i][j] == 2) // se for 2 retorna superior
        if(i > 0) return ((i - 1) * n + j);
    
    if(matriz[i][j] == 4) // se for 4 retorna diagonal superior direita
        if (i > 0 && j < n - 1) return ((i - 1) * n + (j + 1));
    
    if(matriz[i][j] == 8) // se for 8 retorna lado direito
        if (j < n - 1) return (i * n + (j + 1));
    
    if(matriz[i][j] == 16) // se for 1 retorna diagonal inferior direita
        if (i < n - 1 && j < n - 1) return ((i + 1) * n + (j + 1));
    
    if(matriz[i][j] == 32) // se for 32 retorna inferior
        if (i < n - 1) return ((i + 1) * n + j);
    
    if(matriz[i][j] == 64) // se for 64 retorna diagonal inferior esquerda
        if (i < n - 1 && j > 0) return ((i + 1) * n + (j - 1));
    
    if(matriz[i][j] == 128) // se for 128 retorna lado esquerdo
        if (j > 0) return (i * n + (j - 1));
    
    return -1;
}

void preencherListaDeAdjacencia(const vector<vector<int>> &matriz, vector<vector<int>> &lista, const int n) {
    int u = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            int vizinho = retornarVizinho(matriz, i, j, n);
            if(vizinho != -1) {
                lista[u].push_back(vizinho);
                numEntradas[vizinho]++; 
            }

            u++;
        }
}

void preencherMatriz(vector<vector<int>> &matriz, const int n) {
    unsigned char aux;
    
    int i = 0, j = 0;
    while(cin.read(reinterpret_cast<char*>(&aux),1)) {
        matriz[i][j] = static_cast<int>(aux);

        if(i == n-1 && j == n-1) break;
        
        j++;
        if(j == n) {
            j = 0;
            i++;
        }
    }
}

int main(int argc, char **argv) {
    int numLinhas = atoi(argv[1]);
    int limitante;
    if(argc > 2) limitante = atoi(argv[2]);

    vector<vector<int>> matrizDeFluxo(numLinhas, vector<int>(numLinhas));

    preencherMatriz(matrizDeFluxo, numLinhas);

    int numVertices = (numLinhas*numLinhas);

    for(int i = 0; i < numVertices; i++) numEntradas.push_back(0);

    vector<vector<int>> listaDeAdjacencia(numVertices, vector<int>());
    preencherListaDeAdjacencia(matrizDeFluxo, listaDeAdjacencia, numLinhas);
    
    calculaFluxo(listaDeAdjacencia, numVertices);

    switch(limitante) {
        case -1:
            limitanteMenosUm(numLinhas);
            break;
        case -2:
            limitanteMenosDois();
            break;
        default:
            limitanteInteiro(limitante, numLinhas);
            break;
    }

    return 0;
}