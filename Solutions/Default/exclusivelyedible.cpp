// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2286
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

bool losing[48][48][48][48]; //true means when it's your turn 

bool losing_found(int A, int B, int C, int D) {
    for(int a = A - 1; a >= 0; a--) {
        if(losing[a][B][C][D]) {
            return true;
        }
    }

    for(int b = B - 1; b >= 0; b--) {
        if(losing[A][b][C][D]) {
            return true;
        }
    }

    for(int c = C - 1; c >= 0; c--) {
        if(losing[A][B][c][D]) {
            return true;
        }
    }

    for(int d = D - 1; d >= 0; d--) {
        if(losing[A][B][C][d]) {
            return true;
        }
    }

    return false;
}

void solve() {
    int m, n, r, c; cin >> m >> n >> r >> c;
    // cout << "a: " << r << " b: " << c << " c: " << m - 1 - r << " d: " << n - 1 - c << '\n';
    cout << (losing[r][c][m-1-r][n-1-c] ? "Hansel" : "Gretel") << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    losing[0][0][0][0] = 1;

    for(int a = 0; a < 48; a++) {
        for(int b = 0; b < 48; b++) {
            for(int c = 0; c + a < 48; c++) {
                for(int d = 0; b + d < 48; d++) {
                    losing[a][b][c][d] = !losing_found(a,b,c,d);
                }
            }
        }
    }


    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}