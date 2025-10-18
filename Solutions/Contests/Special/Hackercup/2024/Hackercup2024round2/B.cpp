#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int dx[]{0,1,1,1}, dy[]{1,1,0,-1};

vector<int> getcols(int bm) {
    vector<int> cols;
    for(int i = 0; i < 7; i++) {
        cols.push_back(bm % 7);
        bm /= 7;
    }
    return cols;
}

int getbm(vector<int> &cols) {
    int res = 0;
    int mult = 1;
    for(int i = 0; i < 7; i++) {
        res += cols[i] * mult;
        mult *= 7;
    }
    return res;
}

int can_find_with_char(vector<int> &cols, vector<string> &board, char target) {

    for(int i = 0; i < 7; i++) { //col
        for(int j = 0; j < 6; j++) { //row
            for(int dir = 0; dir < 4; dir++) {
                int ok = 1;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[dir] * k;
                    int nj = j + dy[dir] * k;
                    if(ni >= 0 && ni < 7 && nj >= 0 && nj < 6 && board[nj][ni] == target && cols[ni] >= 6 - nj) {

                    } else {
                        ok = 0;
                        break;
                    }
                }

                if(ok) return 1;

            }
        }
    }
    
    return 0;

}

void dfs(int state, vector<int> &states, vector<string> &board, int t) {
    if(states[state] == -1) {
        states[state] = t;
    } else {
        if((states[state] | t) != states[state]) {
            states[state] |= t;
        } else {
            return;
        }
    }

    vector<int> cols = getcols(state);
    int fwin = can_find_with_char(cols, board, 'F');
    int cwin = can_find_with_char(cols, board, 'C');

    if(states[state] == 0) {
        states[state] = fwin * 2 + cwin;
    }

    int cnt = reduce(cols.begin(), cols.end(), 0);
    char needed = '\0';

    if(cnt & 1) {
        needed = 'F';
    } else {
        needed = 'C';
    }

    for(int col = 0; col < 7; col++) {
        if(cols[col] != 6) {
            cols[col]++;
            if(board[6-cols[col]][col] == needed) {
                dfs(getbm(cols), states, board, states[state]);
            }
            cols[col]--;
        }
    }


}

void solve() {
    
    vector<string> board(6);

    for(auto &x : board) cin >> x;

    vector<int> state(823543,-1);

    dfs(0, state, board, 0);

    int hi = state[823542];

    if(hi == 3) {
        cout << "?\n";
    } else if(hi == 2) {
        cout << "F\n";
    } else if(hi == 1) {
        cout << "C\n";
    } else {
        cout << "0\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}