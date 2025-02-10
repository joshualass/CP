#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
int dx []{-1,1,0,0}, dy[]{0,0,-1,1};
class MazeWithKeys {
public:
    int startingPoints(vector<string> a) {
        int res = 0;
        int n = a.size(), m = a[0].size();
        map<char,vector<array<int,2>>> p;
        array<int,2> end = {-1,-1};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] >= 'A' && a[i][j] <= 'Z') {
                    p[a[i][j]].push_back({i,j});
                }
                if(a[i][j] == '*') {
                    end = {i,j};
                }
            }
        }

        auto solve = [&](int sr, int sc) -> bool {
            vector<vector<int>> reachable(n,vector<int>(m));
            set<char> keys;
            queue<array<int,2>> q;
            q.push({sr,sc});
            while(q.size()) {
                auto [r, c]  = q.front();
                q.pop();
                if(a[r][c] == '#' || reachable[r][c] || a[r][c] >= 'A' && a[r][c] <= 'Z' && keys.count(a[r][c]) == 0) continue;
                reachable[r][c] = 1;
                if(a[r][c] >= 'a' && a[r][c] <= 'z' && keys.count(a[r][c] - 'a' + 'A') == 0) {
                    keys.insert(a[r][c] - 'a' + 'A');
                    for(auto [tr,tc] : p[a[r][c] - 'a' + 'A']) {
                        int f = 0;
                        for(int i = 0; i < 4; i++) {
                            int nr = tr + dx[i], nc = tc + dy[i];
                            if(nr >= 0 && nr < n && nc >= 0 && nc < m && reachable[nr][nc]) f = 1;
                        }
                        if(f) {
                            q.push({tr,tc});
                        }
                    }
                }
                for(int i = 0; i < 4; i++) {
                    int nr = r + dx[i], nc = c + dy[i];
                    if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
                        q.push({nr,nc});
                    }
                }
            }
            return reachable[end[0]][end[1]];
        };
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] == '.') {
                    res += solve(i,j);
                }
            }
        }

        vector<vector<int>> reachable(n,vector<int>(m));
        queue<array<int,2>> q;
        q.push(end);
        while(q.size()) {
            auto [r, c]  = q.front();
            q.pop();
            if(reachable[r][c] || a[r][c] == '#' || a[r][c] >= 'A' && a[r][c] <= 'Z') continue;
            reachable[r][c] = 1;
            if(a[r][c] == '.') res--;
            for(int i = 0; i < 4; i++) {
                int nr = r + dx[i], nc = c + dy[i];
                if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    q.push({nr,nc});
                }
            }
        }

        return res;
    }
};
// SOLUTION_END

int main() {
  int n0; cin >> n0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vector<string> arg0(n0);
  for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
  auto c = MazeWithKeys();
  int ret = c.startingPoints(arg0);
  cout << ret;
}