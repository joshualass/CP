#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int n, _k;
vector<string> g, sg;
vector<int> sz;

ll solve(int ind, int nc) {
    // cout << "SOLVE : " << ind << " " << nc << "\n";
    if(ind == _k) {
        // for(int i = 0; i < n; i++) {
        //     cout << sg[i] << "\n";
        // }
        // cout << "\n";
        return nc == 0? 1 : 0;
    }
    ll ans = 0;
    int x = sz[ind];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            //vertical
            if(i + x <= n) {
                int nnc = nc;
                bool is_valid = true;
                for(int k = 0; k < x; k++){
                    int r = i + k, c = j;
                    if(sg[r][c] != '.') is_valid = false;
                    if(g[r][c] == 'O') nnc --;
                    if(g[r][c] == 'X') is_valid = false; 
                }
                if(is_valid) {
                    for(int k = 0; k < x; k++){
                        int r = i + k, c = j;
                        sg[r][c] = 'S';
                    }
                    ans += solve(ind + 1, nnc);
                    for(int k = 0; k < x; k++){
                        int r = i + k, c = j;
                        sg[r][c] = '.';
                    }
                }
            }
            //horizontal
            if(j + x <= n && x > 1){
                int nnc = nc;
                bool is_valid = true;
                for(int k = 0; k < x; k++){
                    int r = i, c = j + k;
                    if(sg[r][c] != '.') is_valid = false;
                    if(g[r][c] == 'O') nnc --;
                    if(g[r][c] == 'X') is_valid = false;
                }
                if(is_valid) {
                    for(int k = 0; k < x; k++){
                        int r = i, c = j + k;
                        sg[r][c] = 'S';
                    }
                    ans += solve(ind + 1, nnc);
                    for(int k = 0; k < x; k++){
                        int r = i, c = j + k;
                        sg[r][c] = '.';
                    }
                }
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> _k;
    g = vector<string>(n);
    sg = vector<string>(n, string(n, '.'));
    for(int i = 0; i < n; i++) cin >> g[i];
    sz = vector<int>(_k);
    for(int i = 0; i < _k; i++) cin >> sz[i];
    int nc = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) nc += g[i][j] == 'O';
    }
    cout << solve(0, nc) << "\n";

    return 0;
}
