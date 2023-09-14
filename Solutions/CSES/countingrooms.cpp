#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<pair<int,int>> dir = {
    {0,-1},
    {0,1},
    {-1,0},
    {1,0}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<string> v(n);
    for(auto &x: v) cin >> x;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(v[i][j] == '.') {
                cnt++;
                queue<pair<int,int>> q;
                q.push({i,j});
                while(q.size()) {
                    pair<int,int> p = q.front();
                    q.pop();
                    if(p.first < 0 || p.first == n || p.second < 0 || p.second == m) {
                        continue;
                    }
                    if(v[p.first][p.second] == '.') {
                        v[p.first][p.second] = '#';
                        for(auto x : dir) {
                            q.push({p.first + x.first, p.second + x.second});
                        }
                    }
                }
            }
        }
    }   
    cout << cnt << "\n";
    return 0;
}