/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Aula do dia 08/12, na qual o professor Salles nos passou a ideia de como seria a implementação baseado na criação do vértice artificial.
As modificações no algoritmo também foram feitas nesse dia.
Pessoas com as quais discuti sobre este exercício:
*/

/**
 *   //////////////////
 *   // MAXIMUM FLOW //
 *   //////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/****************
 * Maximum flow * (Ford-Fulkerson on an adjacency matrix)
 ****************
 * Takes a weighted directed graph of edge capacities as an adjacency 
 * matrix 'cap' and returns the maximum flow from s to t.
 *
 * PARAMETERS:
 *      - cap (global): adjacency matrix where cap[u][v] is the capacity
 *          of the edge u->v. cap[u][v] is 0 for non-existent edges.
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - fnet contains the flow network. Careful: both fnet[u][v] and
 *          fnet[v][u] could be positive. Take the difference.
 *      - ant contains the minimum cut. If ant[v] == -1, then v is not
 *          reachable from s; otherwise, it is reachable.
 * DETAILS:
 * FIELD TESTING:
 *      - Valladolid 10330: Power Transmission
 *      - Valladolid 653:   Crimewave
 *      - Valladolid 753:   A Plug for UNIX
 *      - Valladolid 10511: Councilling
 *      - Valladolid 820:   Internet Bandwidth
 *      - Valladolid 10779: Collector's Problem
 * #include <string.h>
 * #include <queue>
 **/

#include <string.h>
#include <cstring>
#include <iostream>
#include <vector>

#define INF 987654321 //dica do Professor Salles

using namespace std;

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, ant[NN];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( ant, -1, sizeof( ant ) );
        qf = qb = 0;
        ant[q[qb++] = s] = -2;
        while( qb > qf && ant[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( ant[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    ant[q[qb++] = v] = u;

        // see if we're done
        if( ant[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = ant[v]; u >= 0; v = u, u = ant[v] )
            bot = min(bot, cap[u][v] - fnet[u][v] + fnet[v][u]);

        // update the flow network
        for( int v = t, u = ant[v]; u >= 0; v = u, u = ant[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

//Preenchimento das matrizes de capacidade;
void fillCapMatrix(int nVertex, int startEntry, int startExit){
    for(int i = 0; i < nVertex; i++){
        int capacity; 
        cin >> capacity;
        cap[startEntry+i][startExit+i] = capacity;

    }
}

void fillCapMatrixWithLabelInEdges(int nEdges, int startEntry, int startExit){
    for(int i = 0; i < nEdges; i++){
        int v, u, c; 
        cin >> v >> u >> c; u--; v--;
        cap[v+startExit][u+startEntry] = c;
    }
}


int main(){
    int nTest;
    /*A ideia central do algoritmo foi a criação de vértices artificias que combinassem o peso para que o algoritmo funcionasse.*/
    while(cin >> nTest){
        memset(cap, 0, sizeof(cap));
        int startEntry = 1;
        int startExit = 1 + nTest;
        int source = 0;
        int target = 1 + (2*nTest);
        int nVertex = (2*nTest+2);
        int nEdges;

        fillCapMatrix(nTest, startEntry, startExit);
        cin >> nEdges;

        fillCapMatrixWithLabelInEdges(nEdges, startEntry, startExit);
        
        int exitFromSource = 0, arrivingInTarget = 0;
        cin >> exitFromSource >> arrivingInTarget;

        for(int i = 0; i < exitFromSource; i++){
            int vertexFromSource;
            cin >> vertexFromSource;
            vertexFromSource--;
            cap[source][vertexFromSource+startEntry] = INF;
        }

        for(int i = 0; i < arrivingInTarget; i++){
            int vertexToTarget;
            cin >> vertexToTarget;
            vertexToTarget--;
            cap[vertexToTarget+startExit][target] = INF;
        }

        cout << fordFulkerson(nVertex, source, target) << endl;
    }

    return 0;
}