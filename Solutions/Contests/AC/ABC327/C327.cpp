#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<vector<int>> mat(9,vector<int>(9));

    for(auto &x : mat) for(auto &y : x) cin >> y;

    bool ok = 1;

    for(int i = 0; i < 9; i++) {
        set<int> s;
        for(int j = 0; j < 9; j++) {
            s.insert(mat[i][j]);
        }
        if(s.size() != 9) ok = 0;
    }

    for(int i = 0; i < 9; i++) {
        set<int> s;
        for(int j = 0; j < 9; j++) {
            s.insert(mat[j][i]);
        }
        if(s.size() != 9) ok = 0;
    }    

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            set<int> s;
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    s.insert(mat[i*3+k][j*3+l]);
                }
            }
            if(s.size() != 9) ok = 0;
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}