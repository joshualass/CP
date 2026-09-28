#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//Use Prim-like algorithm to construct the MST instead of Kruskal's
//walk up the N nodes in a greedy manner

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<vector<array<ll,2>>> edges(n);
    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq; //c, r
    ll res = 0;
    for(int i = 0; i < q; i++) {
        ll l, r, c; cin >> l >> r >> c;
        l--;
        if(l == 0) {
            pq.push({c,r});
        } else {
            edges[l].push_back({c, r});
        }
        res += c;
    }

    int curr = 1;

    while(pq.size()) {
        array<ll,2> edge = pq.top();
        pq.pop();
        if(curr < edge[1]) {
            res += edge[0];
            for(auto edge : edges[curr]) {
                pq.push(edge);
            }
            curr++;
            pq.push(edge);
        }
    }

    if(curr == n) {
        cout << res << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}