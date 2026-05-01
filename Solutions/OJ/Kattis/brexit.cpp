#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c, p, x, l; cin >> c >> p >> x >> l;

    x--; l--;

    vector<vector<int>> adj(c);
    vector<int> cnts(c);

    for(int i = 0; i < p; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        cnts[a]++;
        cnts[b]++;
    }

    queue<int> q;
    vector<int> in(c, 1);

    q.push(l);

    while(sz(q)) {
        int x = q.front();
        q.pop();
        if(in[x] == 0) continue;
        in[x] = 0;

        // cout << "x : " << x << endl;

        for(int to : adj[x]) {
            cnts[to]--;
            if(cnts[to] * 2 <= sz(adj[to])) {
                q.push(to);
            }
        }
    }

    cout << (in[x] ? "stay" : "leave") << '\n';

    return 0;
}
