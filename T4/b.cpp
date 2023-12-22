/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Como usar ceil/floor no cppreference.com
Pessoas com as quais discuti sobre este exercício:
*/

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>

using namespace std;

void floydWarshall(vector<vector<int>> &mAdj, int np){
    for(int k = 0; k < np; k++){
         for(int i = 0; i < np; i++){
             for(int j = 0; j < np; j++){
                mAdj[i][j] = max(mAdj[i][j], min(mAdj[i][k], mAdj[k][j]));
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
   int n, r;        
   int t = 0;

   while(true){
        cin >> n >> r;
        if(n == 0 && r == 0) break;
        vector<vector<int>> mAdj(n, vector<int>(n, 0));
        int c1, c2, p;
        for(int i = 1; i <= r; i++){
            cin >> c1 >> c2 >> p; c1--; c2--;p--;
            mAdj[c1][c2] = mAdj[c2][c1] = p;
        }

        floydWarshall(mAdj, n);

        int source, seek, pass;
        cin >> source >> seek >> pass; source--; seek--;
        int accessToRoute = mAdj[source][seek];
        cout << "Scenario #" << t+1  << "\n";
        t++;
        cout << "Minimum Number of Trips = " << ceil(double(pass)/accessToRoute) << endl;
        cout << endl;
    }

    return 0;
}