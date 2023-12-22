/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Pessoas com as quais discuti sobre este exercício:
*/
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

#define INF 99999

void floydWarshall(vector<vector<int>> &mAdj, int np){
    for(int k = 0; k < np; k++){
         for(int i = 0; i < np; i++){
             for(int j = 0; j < np; j++){
                if(mAdj[i][j] > mAdj[i][k] + mAdj[k][j] && (mAdj[k][j] != INF)
                        && (mAdj[i][k] != INF))
                    mAdj[i][j]  =  mAdj[i][k] + mAdj[k][j];
            }
        }
    }
}

void printMatrix(const vector<vector<int>> &mAdj){
    for(int i = 0; i < mAdj.size(); i++){
        for(int j = 0; j < mAdj.size(); j++){
            cout << mAdj[i][j] << " ";
        }   
        cout << endl;
    }
}

int main(){
    int t;
    cin >> t;

    for(int i = 0; i < t; i++){
        int numPredios = 0, numEstradas = 0;
        cin >> numPredios;
        cin >> numEstradas;
        vector<vector<int>> mAdj(numPredios, vector<int>(numPredios, INF));
        
        for(int j = 0; j < numEstradas; j++){
            int a, b;
            cin >> a >> b;
            mAdj[a][b] = mAdj[b][a] = 1;
        }

        for(int j = 0; j < numPredios; j++){
            mAdj[j][j] = 0;
        }
        
        int escola = 0, dpi = 0;
        cin >> escola >> dpi;
        floydWarshall(mAdj, numPredios);
        int maxVertex;
        vector<int> sourceDistanceToAllOthers;

        for (int k = 0; k < mAdj.size(); k++) {
           sourceDistanceToAllOthers.push_back(mAdj[escola][k] + mAdj[k][dpi]);
        } 

        auto maxValue = max_element(sourceDistanceToAllOthers.begin(), sourceDistanceToAllOthers.end());
        cout << "Case " << i+1 << ": " << *maxValue << endl;
    }

    return 0;
}