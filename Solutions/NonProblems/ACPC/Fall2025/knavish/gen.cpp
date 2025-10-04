#include "testlib.h"
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
int main(int args_length, char* args[]) {
 
    registerGen(args_length, args, 1);

    int n = stoi(args[1]);
    int m = stoi(args[2]);
    int k = stoi(args[3]);

    int strat = stoi(args[4]);
    int opponent_moves = stoi(args[5]);

    vector<vector<int>> board(n, vector<int>(m));

    if(strat == 0) {
        vector<int> a(n * m);
        iota(a.begin(), a.end());
        shuffle(a.begin(), a.end(), rnd);
        for(int i = 0; i < opponent_moves; i++) {
            int r = a[i] / m, c = a[i] % m;
            board[r][c] = -1;
        }
    } else if(strat == 1) {
        for(int i = 0; i < n; i++) board[i][m - 1] = -1;
        for(int i = 0; i < m; i++) board[n - 1][i] = -1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 0) board[i][j] = rnd.next(999999999) + 1;
        }
    }

    cout << n << " " << m << " " << k << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j] << " \n"[j == m - 1];
        }
    }
 
    return 0;
}
