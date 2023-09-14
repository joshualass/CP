#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};  // DOWN, UP, RIGHT, LEFT

void printAdj(const vector<vector<int>> &adj) {
    cout << " --- adjlist --- \n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i - " << i << ':';
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, sR, sC;
    cin >> R >> C;

    vector<string> lab(R);
    vector<vector<int>> monster(R, vector<int>(C, INT_MAX));
    queue<vector<int>> q;
    for (int i = 0; i < R; i++) {
        cin >> lab[i];
        for (int j = 0; j < C; j++) {
            if (lab[i][j] == '#') {
                monster[i][j] = 0;
            } else if (lab[i][j] == 'M') {
                q.push({i, j, 0});
            } else if (lab[i][j] == 'A') {
                sR = i;
                sC = j;
            }
        }
    }

    while (q.size()) {
        vector<int> v = q.front();
        q.pop();
        int r = v[0];
        int c = v[1];
        if (monster[r][c] <= v[2]) {
            continue;
        }
        monster[r][c] = v[2];
        for (int i = 0; i < 4; i++) {
            int newR = r + dx[i];
            int newC = c + dy[i];
            if (newR >= 0 && newR < R && newC >= 0 && newC < C) {
                q.push({newR, newC, v[2] + 1});
            }
        }
    }
    // for(auto x : lab) cout << x << '\n';

    vector<vector<int>> parents(R, vector<int>(C, -1));
    vector<char> ans(0);
    q.push({sR, sC, 0, -1});
    bool escape = false;
    while (q.size()) {
        vector<int> p = q.front();
        q.pop();
        int r = p[0];
        int c = p[1];
        int step = p[2];
        int dir = p[3];
        if (step >= monster[r][c]) {
            continue;
        }
        if (r == 0 || r == R - 1 || c == 0 || c == C - 1) {
            escape = true;
            while (lab[r][c] != 'A') {
            // cout << "r: " << r << " c: " << c << " dir: " << dir << "\n";
                switch (dir) {
                    case 1:
                        ans.push_back('D');
                        r--;
                        break;
                    case 2:
                        ans.push_back('U');
                        r++;
                        break;
                    case 3:
                        ans.push_back('R');
                        c--;
                        break;
                    case 4:
                        ans.push_back('L');
                        c++;
                        break;
                }
                dir = parents[r][c];

            }
            // cout << "breaking: " << "r: " << r << " c: " << c << " dir: " << dir << "\n";
            
            // printAdj(parents);
            break;
        }
        parents[r][c] = dir;
        monster[r][c] = 0;
        for (int i = 0; i < 4; i++) {
            int newR = r + dx[i];
            int newC = c + dy[i];
            if (newR >= 0 && newR < R && newC >= 0 && newC < C) {
                q.push({newR, newC, step + 1, i + 1});
            }
        }
    }
    if (escape) {
        cout << "YES\n" << ans.size() << "\n";
        reverse(ans.begin(),ans.end());
        for (auto x : ans) cout << x;
        cout << "\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}