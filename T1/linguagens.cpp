/*
README
Fontes de consulta: 
Exercicio maze.cpp e gravação do PER respectivo a essa aula, abordando um problema parecido. Lá, o professor fala sobre
acesso invalido de memória em posições que estavam fora do mapa, o que falhava em alguns testes locais. (Aula do dia 02/11/2022).
Materiais da disciplina, materiais antigos de estrutura de Dados sobre 'overload' do operador de comparação
Pessoas com as quais discuti sobre este exercício:
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void CCCount(vector<vector<char>> &graph,
            vector<vector<bool>> &discovered,
            const int v, const int j,
            const int h, const int w,
            char visitedChar) {
    /*Verificação a fim de não acessarmos posições indevidas da matriz ou vertices ja visitados.*/
    if (v < 0 || v >= h || j < 0 || j >= w || discovered[v][j] || graph[v][j] != visitedChar)
        return;

    discovered[v][j] = true;
    /*Procuramos em todas as direções possíveis, conforme mencionado no excerto: Two letters are “connected” if one is at left, at right, above or below the
    other one.*/
    CCCount(graph, discovered, v - 1, j, h, w, visitedChar);
    CCCount(graph, discovered, v + 1, j, h, w, visitedChar);
    CCCount(graph, discovered, v, j - 1, h, w, visitedChar);
    CCCount(graph, discovered, v, j + 1, h, w, visitedChar);
}

bool compareOverload(const pair<char, int> &a, const pair<char, int> &b){
    //  cout << "A.first: " << a.first << ". B.First: " << b.first << "." << endl;
    //  cout << "A.second: " << a.second << ". B.second: " << b.second << "." << endl;

    /*These lines have to be ordered decreasingly by the number of states. If two languages are spoken in the same number of states, they have to appear
    alphabetically, which means language ‘i’ comes before language ‘q’, for example.*/
    if (a.second != b.second) {
        return a.second > b.second;
    }

    return a.first < b.first;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int h, w; //heidth e widht da matriz - linha e coluna
        cin >> h >> w;

        /* Criação das estruturas: o grafo, propriamente dito, tido como uma matriz. O vetor de vertices visitados, também como matriz e um mapping para fazer
        a contagem dos caracteres (linguagens) faladas em cada estados - basicamente saber o numero de componentes conexos.*/
        vector<vector<char>> graph(h, vector<char>(w));
        vector<vector<bool>> discovered(h, vector<bool>(w, false));
        map<char, int> mapping;

        /*Parsing dos dados para o grafo.*/
        for (int i = 0; i < h; i++) {
            string entry;
            cin >> entry;
            for (int j = 0; j < w; j++) {
                graph[i][j] = entry[j];
            }
        }

        /*Chamada da busca para percorrer o Grafo, se o vertice em questão ainda não foi vistado. Há também o incremento do char lido, de modo a sabermos o numero de "componente conexos"
        baseado na regra de entrada, que é abordada na função invocada.*/
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (!discovered[i][j] ) {
                    char currentChar = graph[i][j];
                    CCCount(graph, discovered, i, j, h, w, currentChar);
                    mapping[currentChar]++;
            }
        }
    }

    /*Método pensado para ordenar: crio um vetor de pares de modo a receber todos os dados do Map para ordená-los seguindo as logicas
    exigidas pelo Output do problema - também abordados na função invocada.*/
    vector<pair<char, int>> pairToSort(mapping.begin(), mapping.end()); 
    sort(pairToSort.begin(), pairToSort.end(), compareOverload);

    cout << "World #" << i + 1 << endl;
    for (auto &data : pairToSort) {
        cout << data.first << ": " << data.second << endl;
    }
}
    return 0;
}
