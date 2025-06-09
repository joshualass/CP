#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int SIZE = 8;
char board[SIZE][SIZE];

int ans = 0;

bool is_valid(int r, int c) {
    // cout << "r: " << r << " c: " << c << " ";
    for(int i = r; i >= 0; i--) {
        if(board[i][c] == 'Q') {
            // cout << "1\n";
            return false;
        }
    }
    for(int i = r + 1; i < SIZE; i++) {
        if(board[i][c] == 'Q') {
            // cout << "2\n";
            return false;
        }
    }
    for(int i = c + 1; i < SIZE; i++) {
        if(board[r][i] == 'Q') {
            // cout << "3\n";
            return false;
        }
    }
    for(int i = c - 1; i >= 0; i--) {
        if(board[r][i] == 'Q') {
            // cout << "4\n";
            return false;
        }
    }
    for(int i = 1; min(r-i,c-i) >= 0; i++) {
        if(board[r-i][c-i] == 'Q') {
            // cout << "5\n";
            return false;
        }
    }
    for(int i = 1; max(r+i,c+i) < SIZE; i++) {
        // cout << "r: " << r << " c: " << c << " i: " << i << "\n";
        if(board[r+i][c+i] == 'Q') {
            // cout << "6\n";
            return false;
        }
    }
    for(int i = 1; (r - i >= 0) && (c + i < SIZE); i++) {
        if(board[r-i][c+i] == 'Q') {
            // cout << "7\n";
            return false;
        }
    }
    for(int i = 1; (r + i < SIZE) && (c - i >= 0); i++) {
        if(board[r+i][c-i] == 'Q') {
            // cout << "8\n";
            return false;
        }
    }
    // cout << "true?\n";
    return true;
}
int counter = 0;

void brutus(int r, int c) {
    // cout << r << " " << c << "\n";
    if(board[r][c] == '*' || !is_valid(r,c)) {
        if(c == SIZE - 1) {
            return;
        }
        brutus(r,c+1);
    } else  {
        if(r == SIZE - 1) {
            ans++;
        } else {
            board[r][c] = 'Q';
            brutus(r+1,0);
            board[r][c] = '.';
        }
        if(c != SIZE - 1) {
            brutus(r,c+1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int r = 0; r < SIZE; r++) {
        string line; cin >> line;
        for(int c = 0; c < SIZE; c++) {
            board[r][c] = line[c];
        }
    }

    brutus(0,0);
    cout << ans << "\n";

    return 0;
}