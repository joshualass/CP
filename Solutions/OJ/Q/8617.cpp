#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> board(n + 24,vector<int>(n + 24));

    int p = 1;
    for(int i = 0; i < n; i += 12) {
        for(int j = 0; j < n; j += 24) {
            for(int k = 0; k < 12; k++) {
                for(int l = 0; l < 12; l++) {
                    board[i+k][j+l] = p;
                }
            }
            p++;
        }
    }
    for(int i = -6; i < n; i += 12) {
        for(int j = 12; j < n; j += 24) {
            for(int k = 0; k < 12; k++) {
                for(int l = 0; l < 12; l++) {
                    if(i + k >= 0 ) {
                        board[i+k][j+l] = p;
                    }
                }
            }
            p++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << " \n"[j == n - 1];
        }
    }

    return 0;
}