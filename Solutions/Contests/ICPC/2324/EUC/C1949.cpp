#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<unordered_set<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 1) {
            pq.push({1,i});
        }
    }

    int merges = 0;
    vector<int> ants(n,1);

    while(pq.size()) {
        pair<int,int> p = pq.top();
        pq.pop();
        int i = p.second;
        // cout << "adj[i].size() : " << adj[i].size() << endl;
        if(adj[i].size() == 0) break;
        int parent = *adj[i].begin();
        if(ants[parent] >= ants[i]) {
            merges++;
            ants[parent] += ants[i];
            adj[parent].erase(i);
            if(adj[parent].size() == 1) {
                pq.push({ants[parent],parent});
            }
        }
    }

    cout << (merges == n-1 ? "YES" : "NO") << '\n';

    return 0;
}