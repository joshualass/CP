#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

void solve() {
    int n; cin >> n;
    vector<string> mat(2);
    for(auto &x : mat) cin >> x;
    queue<array<int,2>> q;
    q.push({0,0});
    vector<vector<int>> visited(2,vector<int>(n,-1));
    while(q.size()) {
        array<int,2> a = q.front();
        q.pop();
        if(visited[a[0]][a[1]] != -1) continue;
        visited[a[0]][a[1]] = 1;
        for(int i = 0; i < 4; i++) {
            int tox = a[0] + dx[i];
            int toy = a[1] + dy[i];
            if(tox >= 0 && tox < 2 && toy >= 0 && toy < n) {
                visited[tox][toy] = 1;
                if(mat[tox][toy] == '>') {
                    q.push({tox,toy+1});
                } else {
                    q.push({tox,toy-1});
                }
            }
        }
    }
    cout << (visited[1][n-1] == 1 ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}