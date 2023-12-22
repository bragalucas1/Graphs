/*
README
Fontes de consulta: Dúvidas no fórum do Moodle.
Pessoas com as quais discuti sobre este exercício:
*/
#include <vector>
#include <iostream>
#include <climits>
#include <map>
#include <cmath>

using namespace std;
#define INF 99999

void floydWarshall(vector<vector<double>> &mAdj, int np){
    for(int k = 0; k < np; k++){
         for(int i = 0; i < np; i++){
             for(int j = 0; j < np; j++){
                if(mAdj[i][j] > mAdj[i][k] + mAdj[k][j])
                    mAdj[i][j]  =  mAdj[i][k] + mAdj[k][j];
            }
        }
    }
}

void printMatrix(const vector<vector<double>> &mAdj){
    for(int i = 0; i < mAdj.size(); i++){
        for(int j = 0; j < mAdj.size(); j++){
            cout << mAdj[i][j] << " ";
        }   
        cout << endl;
    }
}

bool checkDiagonal(const vector<vector<double>> &mAdj){
    for (int i = 0; i < mAdj.size(); ++i) {
        if (mAdj[i][i] < 0) {
            return true;
        }
    }
    return false; 
}

int main(){
    int n;
    int t = 0;
    while(n != 0){
        cin >> n;
        if(n == 0) break;
        map<string, double> map;

        for(int i = 0; i < n; i++){
            string name;
            cin >> name;
            double id = map.size();
            map[name] = id;
        }


        int k;
        cin >> k;
        vector<vector<double>> mAdj(n, vector<double>(n, INF));

        for(int j = 0; j < k; j++){
            string name1, name2;
            double rate;
            cin >> name1 >> rate >> name2;
            mAdj[map[name2]][map[name1]]  = log(1/rate);       
        }   
    
        floydWarshall(mAdj, n);

        cout << "Case " << t+1 << ": " << (checkDiagonal(mAdj) ? "Yes" : "No") << endl;
        t++;
    }
    return 0;
}