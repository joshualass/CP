#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
hints
1. the order doesn't really matter. i.e. we can kind of ignore the condition "After each query, every element of 𝑎 should be a non-negative integer."
2. think of it like a graph
3. recall our discussion on this problem https://codeforces.com/problemset/problem/1994/F

Do ^^, then construct a tree, and greedy that way. The problem seemed super similar to StarDew Valley approach where you construct a tree from the graph, and it was!
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    vector<array<int,2>> edges(q);
    vector<multiset<int>> adj(n);

    for(int i = 0; i < q; i++) {
        cin >> edges[i][0] >> edges[i][1];
        edges[i][0]--;
        edges[i][1]--;
        adj[edges[i][0]].insert(edges[i][1]);
        adj[edges[i][1]].insert(edges[i][0]);
    }

    vector<int> par(n);
    map<array<int,2>, int> m;

    auto dfs = [&](auto self, int i) -> void {
        while(adj[i].size()) {
            int child = *adj[i].begin();
            adj[i].erase(adj[i].find(child));
            adj[child].erase(adj[child].find(i));
            self(self, child);
            if(par[child]) {
                par[child] ^= 1;
                m[{child,i}]++;
            } else {
                par[i] ^= 1;
                m[{i,child}]++;
            }
        }
    };

    for(int i = 0; i < n; i++) {
        dfs(dfs,i);
    }

    par.assign(n,0);

    for(int i = 0; i < q; i++) {
        if(m.count(edges[i])) {
            m[edges[i]]--;
            if(m[edges[i]] == 0) {
                m.erase(edges[i]);
            }
            cout << 'x';
            if(par[edges[i][0]]) {
                cout << '-';
            } else {
                cout << '+';
            }
            par[edges[i][0]] ^= 1;
        } else {
            swap(edges[i][0], edges[i][1]);
            m[edges[i]]--;
            if(m[edges[i]] == 0) {
                m.erase(edges[i]);
            }
            cout << 'y';
            if(par[edges[i][0]]) {
                cout << '-';
            } else {
                cout << '+';
            }
            par[edges[i][0]] ^= 1;
        }
        cout << '\n';
    }

    return 0;
}