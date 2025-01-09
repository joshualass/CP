#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4] {1,0,-1,0}, dy[4]{0,-1,0,1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;
    vector<string> board(r);
    int mc = 0;
    for(auto &x : board) {
        cin >> x;
        mc += c - count(x.begin(), x.end(), '.');    
    }

    vector<string> res;
    vector vis(r,vector<bool>(c));

    auto simulate = [&](int sr, int sc, int dir) -> bool {
        // cout << "sr : " << sr << " sc : " << sc << '\n';
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                vis[i][j] = 0;
            }
        }
        int vc = 0;

        auto go = [&](int rpos, int cpos, int dir) -> array<int,3> {
            if(board[rpos][cpos] == '/') {
                dir ^= 1;
                if(vis[rpos][cpos] == 0) {
                    vc++;
                }
            } else if(board[rpos][cpos] == '\\') {
                dir ^= 3;
                if(vis[rpos][cpos] == 0) {
                    vc++;
                }
            }   

            vis[rpos][cpos] = 1;

            return {rpos + dy[dir], cpos + dx[dir], dir};
        };

        while(1) {
            array<int,3> res = go(sr,sc,dir);
            int nr = res[0], nc = res[1], ndir = res[2];

            // cout << "nr : " << nr << " nc : " << nc << " dir : " << dir << '\n';

            if(nr < 0 || nr >= r || nc < 0 || nc >= c) break;
            sr = nr, sc = nc, dir = ndir;

        }
        // cout << "vc : " << vc << '\n';
        return vc == mc;
    };

    for(int i = 0; i < c; i++) {
        if(simulate(0,i,3)) {
            res.push_back("N" + to_string(i + 1));
        }
        if(simulate(r - 1, i, 1)) {
            res.push_back("S" + to_string(i + 1));
        }
    }

    for(int i = 0; i < r; i++) {
        if(simulate(i,0,0)) {
            res.push_back("W" + to_string(i + 1));
        }
        if(simulate(i,c - 1, 2)) {
            res.push_back("E" + to_string(i + 1));
        }
    }

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

    return 0;
}