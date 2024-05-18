#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    
    vector<array<int,3>> res;
    vector<vector<int>> board(4,vector<int>(n));
    for(auto &x : board) for(auto &y: x) cin >> y;
    bool poss = 0;
    for(int i = 0; i < n; i++) {
        if(board[0][i] == board[1][i] && board[1][i] != 0) {
            res.push_back({board[0][i], 1, i + 1});
            board[1][i] = 0;
        }
        if(board[2][i] == board[3][i] && board[2][i] != 0) {
            res.push_back({board[2][i], 4, i + 1});
            board[2][i] = 0;
        }
        if(board[1][i] == 0 || board[2][i] == 0) poss = 1;
    }
    if(!poss) {
        cout << "-1\n";
        return 0;
    }
    int curr = 0, curc = 0;

    int nocar = 0;
    while(nocar++ < 200) {
        int nextr, nextc;
        if(curr == 0) {
            if(curc == n -1) {
                nextr = 1;
                nextc = n - 1;
            } else {
                nextr = 0;
                nextc = curc + 1;
            }
        } else {
            if(curc == 0) {
                nextr = 0;
                nextc = 0;
            } else {
                nextr = 1;
                nextc = curc - 1;
            }
        }
        // cout << "curr : " << curr << " curc : " << curc << " nextr : " << nextr << " nextc : " << nextc << '\n';
        // cout << "board\n" << board;
        if(board[nextr+1][nextc] != 0) nocar = 0;
        if(nextr == 0 && board[nextr][nextc] == board[nextr+1][nextc] && board[nextr][nextc] != 0) {
            res.push_back({board[nextr][nextc], 1, nextc + 1});
            board[1][nextc] = 0;
        }
        if(nextr == 1 && board[2][nextc] == board[3][nextc] && board[3][nextc] != 0) {
            res.push_back({board[2][nextc], 4, nextc + 1});
            board[2][nextc] = 0;
        }
        if(board[curr+1][curc] == 0 && board[nextr+1][nextc] != 0) {
            res.push_back({board[nextr+1][nextc], curr+2,curc+1});
            swap(board[curr+1][curc], board[nextr+1][nextc]);
        }
        curr = nextr;
        curc = nextc;
    }
    cout << res.size() << '\n';
    for(auto a : res) {
        cout << a[0] << " " << a[1] << " " << a[2] << '\n';
    }

    return 0;
}