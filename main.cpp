#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

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



int main(int argc, char* argv[]) {

    int x, y, time;
    int N, M, K;

    fstream newfile;
    //newfile.open(argv[1], std::ios::in);
    newfile.open("testni_primer1.txt", std::ios::in);
    if (! newfile.is_open()) {
        cout << "Error opening file";
        return 0;
    }
    newfile >> N;
    newfile >> M;
    newfile >> K;

    int grid[N][M];
    int A[K+1][2];


    for(int i = 0; i < K+1; i++){
        A[i][0] = INT_MAX;
        A[i][1] = INT_MAX;
    }

    A[0][0] = 0;
    int RESULT[K+1];

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
        newfile >> x;
        newfile >> y;
        newfile >> time;
        grid[x-1][y-1] = time;
    }
    newfile.close();
    /*for (int i = 0; i < K; i++) {
        cin >> x >> y >> time;
        grid[x-1][y-1] = time;
    }*/

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

    //pridomi indekse otokov po vrsticah v obratni smeri
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
        if ( i > 0)
        {
            for (int j = 0; j < K+1; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    if (A[j][k] != INT_MAX)
                    {
                        A[j][k] += 1;
                    }
                }
            }
        }
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
                    bool inf1 = false, inf2 = false;
                    int SUM1 = A_[j - KOMBINACIJE[m].size()][0];
                    if(SUM1 == INT_MAX)
                        inf1 = true;
                    int SUM2 = A_[j - KOMBINACIJE[m].size()][0];
                    if(SUM2 == INT_MAX)
                        inf2 = true;
                    int step = 0;

                    for(int n = 0; n < KOMBINACIJE[m].size(); n++){
                        SUM1 += abs(KOMBINACIJE[m][n] - step) + grid[i][KOMBINACIJE[m][n]];
                        SUM2 += abs(KOMBINACIJE[m][n] - step) + grid[i][KOMBINACIJE[m][n]];
                        step = KOMBINACIJE[m][n];
                    }
                    if(inf1)
                        SUM1 = INT_MAX;
                    if(inf2)
                        SUM2 = INT_MAX;
                    seznamResult.push_back(SUM1);
                    seznamA0.push_back((inf1) ? INT_MAX : (SUM1+step));
                    seznamA1.push_back((inf2) ? INT_MAX : (SUM2+korakiDoKonca-step));

                }
                if(i > 0){
                    vector<vector<int>> KOMBINACIJE_reverse;
                    for (int k = KOMBINACIJE.size()-1; k >= 0; --k) {
                        KOMBINACIJE_reverse.push_back(KOMBINACIJE[k]);
                    }
                    for(int m = 0; m < KOMBINACIJE_reverse.size(); m++){
                        bool inf1 = false, inf2 = false;

                        int SUM1 = A_[j - KOMBINACIJE_reverse[m].size()][1];
                        if(SUM1 == INT_MAX)
                            inf1 = true;
                        int SUM2 = A_[j - KOMBINACIJE_reverse[m].size()][1];
                        if(SUM2 == INT_MAX)
                            inf2 = true;
                        int step = korakiDoKonca;

                        for(int n = KOMBINACIJE_reverse[m].size()-1; n >= 0 ; n--){
                            SUM1 += abs(step - KOMBINACIJE_reverse[m][n]) + grid[i][KOMBINACIJE_reverse[m][n]];
                            SUM2 += abs(step - KOMBINACIJE_reverse[m][n]) + grid[i][KOMBINACIJE_reverse[m][n]];
                            step = KOMBINACIJE_reverse[m][n];
                        }
                        if(inf1)
                            SUM1 = INT_MAX;
                        if(inf2)
                            SUM2 = INT_MAX;
                        seznamResult.push_back(SUM1);
                        seznamA0.push_back((inf1) ? INT_MAX : (SUM1+step));
                        seznamA1.push_back((inf2) ? INT_MAX : (SUM2+korakiDoKonca-step));

                    }

                }
                seznamResult.push_back(RESULT[j]);
                seznamA0.push_back(A_[j][0]);
                seznamA1.push_back(A_[j][1]);
                RESULT[j] = *min_element(seznamResult.begin(), seznamResult.end());
                A[j][0] = *min_element(seznamA0.begin(), seznamA0.end());
                A[j][1] = *min_element(seznamA1.begin(), seznamA1.end());

            }

        }

    }
    //print RESULT
    for (int i = 1; i < K+1; ++i) {
        cout << RESULT[i] << " ";
    }





    return 0;
}