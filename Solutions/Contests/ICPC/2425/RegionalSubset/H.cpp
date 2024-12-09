#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, g, d, m; cin >> n >> g >> d >> m;
    vector<int> inside(1e6);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        inside[x] = 1;
    }

    vector<vector<int>> sands(g);
    for(int i = 0; i < g; i++) {
        int cnt; cin >> cnt;
        for(int j = 0; j < cnt; j++) {
            int x; cin >> x;
            x--;
            sands[i].push_back(x);
        }
    }

    vector<vector<int>> adj(1e6);

    for(int i = 0; i < d; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    queue<int> q;

    for(int i = 0; i < 1e6; i++) {
        if(inside[i]) {
            q.push(i);
            inside[i] = 0;
        }
    }

    int incnt = 0;
    set<int> s;

    while(q.size()) {
        int x = q.front();
        q.pop();
        if(inside[x]) continue;
        inside[x] = 1;
        incnt++;
        s.insert(x);
        for(int c : adj[x]) {
            q.push(c);
        }
    }

    int ok = incnt <= m;
    int found = 0;

    for(int i = 0; i < g; i++) {
        int cntsame = 0;
        for(int x : sands[i]) {
            if(s.count(x)) {
                cntsame++;
            }
        }
        if(cntsame == incnt) {
            found = 1;
        }
    }

    cout << (ok && found ? "masterpiece" : "disaster") << '\n';

    return 0;
}