#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int evenrows [9] = {1,2,2,3,3,3,4,4,5};
int evencols [9] = {3,2,4,1,3,5,2,4,3};
int oddrows [12] = {1,1,2,2,2,3,3,4,4,4,5,5};
int oddcols [12] = {2,4,1,3,5,2,4,1,3,5,2,4};

bool checker(vector<vector<bool>> &board, bool odd) {
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            if((i + j & 1) == odd) {
                if(board[i-1][j-1] && board[i+1][j-1] && board[i-1][j+1] && board[i+1][j+1] && board[i][j]) return 0;
            }
        }
    }
    return 1;
}

void solve() {
    vector<vector<bool>> mat(7,vector<bool>(7));
    for(int i = 0; i < 7; i++) {
        string s; cin >> s;
        for(int j = 0; j < 7; j++) {
            if(s[j] == 'B') mat[i][j] = 1;
        }
    }

    int evenans = 69, oddans = 69;
    vector<vector<bool>> board = mat;
    for(int i = 0; i < 1 << 9; i++) {
        for(int bit = 0; bit < 9; bit++) {
            if((i >> bit) & 1) {
                board[evenrows[bit]][evencols[bit]] = 0;
            }
        }
        // if(i == 511) {
        //     cout << "board\n" << board;
        // }
        if(checker(board, 0)) {
            evenans = min(evenans, __builtin_popcount(i));
        }
        for(int bit = 0; bit < 9; bit++) {
            if((i >> bit) & 1) {
                board[evenrows[bit]][evencols[bit]] = mat[evenrows[bit]][evencols[bit]];
            }
        }
    }

    for(int i = 0; i < 1 << 12; i++) {
        for(int bit = 0; bit < 12; bit++) {
            if((i >> bit) & 1) {
                board[oddrows[bit]][oddcols[bit]] = 0;
            }
        }
        if(checker(board, 1)) {
            // if(__builtin_popcount(i) == 3) {
            //     cout << "bpc i = 3 board\n" << board;
            // }
            oddans = min(oddans, __builtin_popcount(i));
        }
        for(int bit = 0; bit < 12; bit++) {
            if((i >> bit) & 1) {
                board[oddrows[bit]][oddcols[bit]] = mat[oddrows[bit]][oddcols[bit]];
            }
        }
    }
    // cout << "e : " << evenans << " O : " << oddans << '\n';
    cout << evenans + oddans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}