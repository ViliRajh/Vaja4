#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> kombinacija;
vector<int> curr;

void combinations(vector<int> &arr, vector<int> &curr, int index, int n) {
    if (index == n) {
        // Izpisemo trenutno kombinacijo
        if( curr.size() != 0)
            kombinacija.push_back(curr);
        return;
    }

    // Recursive step: izberemo ali element na mestu `index` vključimo v kombinacijo ali ne
    // Če ga ne vključimo, rekurzija gre naprej brez tega elementa
    combinations(arr, curr, index + 1, n);

    // Če ga vključimo, ga dodamo v trenutno kombinacijo in rekurzija gre naprej
    curr.push_back(arr[index]);
    combinations(arr, curr, index + 1, n);

    // Ko se rekurzija vrne, element izberemo iz trenutne kombinacije
    curr.pop_back();
}



int main() {

    int x, y, time;
    int N, M, K;

    cin >> N >> M >> K;

    int grid[N][M];
    int A[K+1][2];
    //nastavi A na INTMAX
    for(int i = 0; i < K+1; i++){
        A[i][0] = INT_MAX;
        A[i][1] = INT_MAX;
    }
    A[0][0] = 0;
    int RESULT[K+1];
    //nastavi RESULT na INTMAX
    for(int i = 0; i < K+1; i++){
        RESULT[i] = INT_MAX;
    }
    RESULT[0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < K; i++) {
        cin >> x >> y >> time;
        //islands.push_back(Island(x, y, time));
        grid[x-1][y-1] = time;
    }

    //pridomi indekse otokov po vrsticah
    vector<vector<int>> vrstice;
    for (int i = 0; i < N; i++) {
        vector<int> vrstica;
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != INT_MAX) {
                vrstica.push_back(j);
            }
        }
        vrstice.push_back(vrstica);
    }

    vector<vector<int>> vrstice_reverse;
    for (int i = 0; i < N ; ++i) {
        vector<int> vrstica;
        for (int j = M-1; j >= 0; --j) {
            if (grid[i][j] != INT_MAX) {
                vrstica.push_back(j);
            }
        }
        vrstice_reverse.push_back(vrstica);
    }

    int korakiDoKonca = M-1;
    int stOtokov= 0;

    for (int i = 0; i < N; i++) {
        if ( i > 0){
            for (int j = 0; j < K+1; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (A[j][k] != INT_MAX){
                        A[j][k] += 1;
                    }
                }
            }
        }
        //skopiraj A v A_     //to prever ce je ok
        int A_[K+1][2];
        for (int j = 0; j < K+1; ++j) {
            for (int k = 0; k < 2; ++k) {
                A_[j][k] = A[j][k];
            }
        }

        stOtokov += vrstice[i].size();
        for (int j = 0; j < stOtokov+1; j++ ){
            if (j == 0) {
                if (i == 0) {
                    A[0][1] = min(A_[0][1], A_[0][0] + korakiDoKonca);
                }
                else {
                    A[0][1] = min(A_[0][1], A_[0][0] + korakiDoKonca);
                    A[0][0] = min(A_[0][0], A_[0][1] + korakiDoKonca);
                }
            }
            else
            {
                //tu pazi ce treba z for skozi al ne
               vector<vector<int>> KOMBINACIJE;
               for (int k = vrstice[i].size(); k > 0; --k) {
                  kombinacija.erase(kombinacija.begin(), kombinacija.end());
                  curr.erase(curr.begin(), curr.end());
                  combinations(vrstice[i], curr, 0, vrstice[i].size());
                  for (int l = 0; l < kombinacija.size(); ++l) {
                    KOMBINACIJE.push_back(kombinacija[l]);
                  }
              }

              vector<int> seznamResult;
              vector<int> seznamA0;
              vector<int> seznamA1;


              for(int m = 0; m < KOMBINACIJE.size(); m++){
                  int SUM1, SUM2;

              }
            }
        }

    }






    return 0;
}