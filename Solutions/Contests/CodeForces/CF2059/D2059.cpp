#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, s1, s2; cin >> n >> s1 >> s2;
    s1--; s2--;
    vector<vector<int>> a(n), b(n);
    set<int> s;
    set<array<int,2>> e;
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int c, d; cin >> c >> d;
        c--; d--;
        a[c].push_back(d);
        a[d].push_back(c);
        e.insert({min(c,d),max(c,d)});
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        int c, d; cin >> c >> d;
        c--; d--;
        b[c].push_back(d);
        b[d].push_back(c);
        if(e.count({min(c,d),max(c,d)})) {
            s.insert(c);
            s.insert(d);
        }
    }

    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    pq.push({0,s1,s2});
    vector<vector<int>> v(n,vector<int>(n,-1));
    while(pq.size()) {
        auto [c, i, j] = pq.top();
        pq.pop();
        if(v[i][j] != -1) continue;
        v[i][j] = c;
        for(int ta : a[i]) {
            for(int tb : b[j]) {
                if(v[ta][tb] == -1) {
                    pq.push({c + abs(ta-tb), ta, tb});
                }
            }
        }
    }
    int res = INT_MAX;
    for(int x : s) {
        if(v[x][x] != -1) res = min(res,v[x][x]);
    }
    cout << (res == INT_MAX ? -1 : res) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}