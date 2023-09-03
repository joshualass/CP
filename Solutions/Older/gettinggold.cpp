#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C; cin >> C >> R;
    vector<vector<char>> map(R,vector<char>(C));
    int startR = -1;
    int startC = -1;

    for(int r = 0; r < R; r++) {
        string line; cin >> line;
        for(int c = 0; c < C; c++) {
            map[r][c] = line[c];
            if(map[r][c] == 'P') {
                startR = r;
                startC = c;
                map[r][c] = '.';
            }
        }
    }

    queue<pair<int,int>> q;
    q.push({startR,startC});
    vector<vector<bool>> visited(R,vector<bool>(C,false));
    int gold = 0;
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        int r = p.first;
        int c = p.second;
        if(visited[r][c] || map[r][c] == '#') {
            continue;
        }
        visited[r][c] = true;
        if(map[r][c] == 'G') {
            gold++;
        }
        bool trap = false;
        if(r != 0 && map[r-1][c] == 'T') {
            trap = true;
        }
        if(c != 0 && map[r][c-1] == 'T') {
            trap = true;
        }
        if(r != R-1 && map[r+1][c] == 'T') {
            trap = true;
        }
        if(r != C-1 && map[r][c+1] == 'T') {
            trap = true;
        }
        if(!trap) {
            q.push({r-1,c});
            q.push({r+1,c});
            q.push({r,c+1});
            q.push({r,c-1});
        }
    }
    cout << gold << "\n";
    return 0;
}