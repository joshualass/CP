#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    while(n-->0) {
        int m; cin >> m;
        vector<vector<int>> prefs(m, vector<int>(8));
        vector<vector<int>> flips(m + 1, vector<int>(8));
        for(int i = 0; i < m; i++) {
            for(int t = 0; t < 8; t++) {
                cin >> prefs[i][t];
                prefs[i][t]--;
                // int num; cin >> num;
                // num--;
                // prefs[i][num] = t; //t is the scenario, 
            }
        }
        for(int i = 0; i < 8; i++) {
            flips[m][i] = i;
        }
//        reverse(prefs.begin(), prefs.end());
        for(int i = m - 1; i >= 0; i--) {
            for(int t = 0; t < 8; t++) { //given orientation t
                int most = 8;
                int index = 0;
                for(int s = 0; s < 3; s++) { //try 3 different flips
                    int num = t ^ (1 << s);
                    int value = flips[i + 1][num];
                    if(prefs[i][value] < most) {
                        index = s;
                        most = prefs[i][value];
                    }
//                     for(int f = 0; f < 8; f++) { //keep the best variation
//                             if() {


//                                 break;
//                             }
//                         if(prefs[i][f] == flips[i+1][num]) {
//                             if(f < most) {
//                                 most = f;
//                                 index = s;
//                             }
// //                            cout << "i: " << i << " t: " << t << " s: " << s << " f: " << f << " pref: " << prefs[i][f] << " num: " << num << '\n';
//                             break;
//                         }
//                     }
                }
                flips[i][t] = t ^ (1 << index);
            }
        }
        cout << "printing flips array\n";
        for(vector<int> x : flips) {
            for(int y : x) { 
                cout << y << ' ';
            }
            cout << '\n';
        }
        int index = 0;
        for(int i = 0; i < m; i++) {
            index = flips[i][index];
        }
        cout << index << '\n';
    }

    return 0;
}

/*
1
3
8 6 3 1 2 4 5 7
8 3 6 5 1 2 7 4
1 2 3 4 5 6 7 8
*/