#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll positions = 0;
int n;

vector<vector<char>> fillDown(vector<vector<char>> board, int r, int c, int size) {
    for(int i = r; i < r + size; i++) {
        board[i][c] = 'X';
    }
    return board;
}

vector<vector<char>> fillLeft(vector<vector<char>> board, int r, int c, int size) {
    for(int i = c; i < c + size; i++) {
        board[r][i] = 'X';
    }
    return board;
}

map<int, int> bye(map<int,int> ships, int index) {
    ships[index]--;
    if(ships[index] == 0) {
        ships.erase(index);
    }
    return ships;
}

void battle(vector<vector<char>> board, map<int,int> ships, int position, int remain, int mult) {

    if(ships.empty()) {
        if(remain == 0) {
            positions += mult;
        }
        return;
    }
    if(position == n * n) {
        return;
    }
    
    for(pair<int, int> p : ships) {
        int r = position / n;
        int c = position % n;
        int size = p.first;
        if(r + size <= n) {
            int O = 0;
            bool flag = true;
            for(int i = r; i < r + size; i++) {
                if(board[i][c] == 'X') {
                    flag = false;
                    break;
                }
                if(board[i][c] == 'O') {
                    O++;
                }
            }
            if(flag) {
                battle(fillDown(board, r, c, size), bye(ships, p.first), position + 1, remain - O, mult * p.second);
            }
        }

        if(size != 1) {

            if(c + size <= n) {
                int O = 0;
                bool flag = true;
                for(int i = c; i < c + size; i++) {
                    if(board[r][i] == 'X') {
                        flag = false;
                        break;
                    }
                    if(board[r][i] == 'O') {
                        O++;
                    }
                }
                if(flag) {
                    battle(fillLeft(board, r, c, size), bye(ships, p.first), position + 1, remain - O, mult * p.second);
                }
            }

        }
    }
    battle(board, ships, position + 1, remain, mult); // don't use any ships in this position
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> n >> k;

    vector<vector<char>> v(n, vector<char>(n));
    int empty = 0;
    int req = 0;
    for(int r = 0; r < n; r++) {
        string line;
        cin >> line;
        for(int c = 0; c < n; c++) {
            char ch = line[c];
            v[r][c] = ch;
            if(ch == '.') {
                empty++;
            }
            if(ch == 'O') {
                req++;
            }
        }
    }

    map<int,int> m;
    for(int i = 0; i < k; i++) {
        int num; cin >> num;
        if(m.find(num) == m.end()) {
            m[num] = 1;
        } else {
            m[num]++;
        }
    }

    battle(v, m, 0, req, 1);
    
    cout << positions;

    return 0;
}