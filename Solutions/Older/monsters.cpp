#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, m; cin >> n >> m;
        vector<int> monsters(n);
        vector<vector<int>> adj(n);
        vector<bool> tried(n);
        for(int i = 0; i < n; i++) {
            cin >> monsters[i];
        }
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            adj[--a].push_back(--b);
            adj[b].push_back(a);
        }
        bool flag = false;
        for(int i = 0; i < n; i++) {
            if(tried[i]) {
                continue;
            }
            tried[i] = true;
            vector<bool> visited(n);
            int power = 0;
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            pq.push({monsters[i],i});
            while(pq.size()) {
                pair<int,int> p = pq.top();
                // cout << "i: " << i << "pair: " << p.first << " " << p.second << "\n";
                pq.pop();
                if(p.first > power) {
                    break;
                }
                int index = p.second;
                if(visited[index]) {
                    continue;
                }
                tried[index] = true;
                visited[index] = true;
                power++;
                for(int x : adj[index]) {
                    pq.push({monsters[x],x});
                }
            }
            if(power == n) {
                flag = true;
                break;
            }
        }
        cout << (flag ? "YES" : "NO") << "\n";
    }


    return 0;
}