#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>

using namespace std;

vector<int> adj[200005];
bool is_hometown[200005];
int subtree_size[200005];
int n, k;
int center_city = -1;

void dfs(int u, int p, int root) {
    subtree_size[u] = is_hometown[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, root);
            subtree_size[u] += subtree_size[v];
        }
    }

    if (center_city == -1) {
        bool ok = true;
        for (int v : adj[u]) {
            if (v != p && subtree_size[v] > k) {
                ok = false;
                break;
            }
        }
        if (ok && (2 * k - subtree_size[u]) <= k) {
            center_city = u;
        }
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> hometowns(2 * k);
    for (int i = 0; i < 2 * k; ++i) {
        cin >> hometowns[i];
        is_hometown[hometowns[i]] = true;
    }

    dfs(hometowns[0], -1, 0);

    cout << 1 << endl;
    cout << center_city << endl;

    vector<array<int,2>> pairings;

    priority_queue<array<int,2>> pq;

    vector<vector<int>> a;
    auto dfs2 = [&](auto self, int i, int p) -> void {
        if(is_hometown[i]) a.back().push_back(i);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
    };

    for(int c : adj[center_city]) {
        a.push_back({});
        dfs2(dfs2, c, center_city);
        if(a.back().size()) {
            pq.push(array<int,2>{(int)a.back().size(), (int)a.size() - 1});
        }
    }

    if(is_hometown[center_city]) {
        pq.push({1,(int)a.size()});    
        a.push_back({center_city});
    }

    while(pq.size()) {
        array<int,2> b = pq.top();
        pq.pop();
        array<int,2> c = pq.top();
        pq.pop();
        pairings.push_back({a[b[1]].back(), a[c[1]].back()});
        a[b[1]].pop_back();
        a[c[1]].pop_back();
        if(a[b[1]].size()) {
            pq.push({(int)a[b[1]].size(), b[1]});
        }
        if(a[c[1]].size()) {
            pq.push({(int)a[c[1]].size(), c[1]});
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << pairings[i][0] << " " << pairings[i][1] << " " << center_city << endl;
    }

    return 0;
}