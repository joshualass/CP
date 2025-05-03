#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
5
1 2
2 3
3 4
4 5
5 6




*/

void solve() {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector g(40,vector(40, vector(40, vector<int>(40))));

    for(int i = 0; i < 40; i++) {
        for(int j = 0; j < 40; j++) {
            for(int k = 0; k < 40; k++) {
                for(int l = 0; l < 40; l++) {
                    int p = (i == 3 && j == 4 && k == 5 && l == 2);
                    // p = 0;
                    if(i == k && j == l) {
                        g[i][j][k][l] = -1;
                        continue;
                    }
                    int w = 0;
                    for(int m = 1; m <= i; m++) {
                        if((i - m) == k && j == l) break;
                        if(g[i-m][j][k][l] == 0) {
                            w = 1;
                            if(p) {
                                cout << "found win 0 m : " << m << '\n';
                            }
                        }
                    }
                    for(int m = 1; m <= j; m++) {
                        if((j - m) == l && i == k) break;
                        if(g[i][j-m][k][l] == 0) {
                            w = 1;
                            if(p) {
                                cout << "found win 1 m : " << m << '\n';
                            }
                        }
                    }
                    for(int m = 1; m <= k; m++) {
                        if((k - m) == i && j == l) break;
                        if(g[i][j][k-m][l] == 0) {
                            w = 1;
                            if(p) {
                                cout << "found win 2 m : " << m << '\n';
                            }
                        }
                    }
                    for(int m = 1; m <= l; m++) {
                        if((l - m) == j && i == k) break;
                        if(g[i][j][k][l-m] == 0) {
                            w = 1;
                            if(p) {
                                cout << "found win 3 m : " << m << '\n';
                            }
                        }
                    }
                    g[i][j][k][l] = w;
                }
            }
        }
    }

    int tc; cin >> tc;
    for(int i = 0; i < tc; i++) {
        int sx, sy; cin >> sx >> sy;
        cout << "sx : " << sx << " sy : " << sy << '\n';
        for(int i = 0; i < 40; i++) {
            for(int j = 0; j < 40; j++) {
                if(g[sx][sy][i][j] == -1) {
                    cout << '-' << " \n"[j == 40 - 1];
                } else {
                    cout << g[sx][sy][i][j] << " \n"[j == 40 - 1];
                }
            }
        }
    }


    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}