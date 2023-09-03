#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll dinic(int source, int sink, int n, vector<vector<ll>> capacity, vector<vector<ll>> adj) {
    vector<vector<ll>> transpose(n);
    for(int i = 0; i < adj.size(); i++) {
        for(int y : adj[i]) {
            transpose[y].push_back(i);
        }
    }
    vector<int> levels(n,-1);
    ll answer = 0;
    while(true) {
        fill(levels.begin(), levels.end(),-1);
        queue<int> q;
        q.push(source);
        levels[source] = 0;
        while(q.size()) {
            int x = q.front();
            q.pop();
            for(int y : adj[x]) {
                if(levels[y] == -1 && capacity[x][y] != 0) {
                    levels[y] = levels[x] + 1;
                    q.push(y);
                }
            }
            for(int y : transpose[x]) {
                if(levels[y] == -1 && capacity[x][y] != 0) {
                    levels[y] = levels[x] + 1;
                    q.push(y);
                }
            }
        }
        if(levels[sink] == -1) {
            break;
        }
        while(true) {
            stack<int> nodes;
            nodes.push(source);
            while(nodes.size()) {
                int curr = nodes.top();
                bool found = false;
                int next = -1;
                if(curr == sink) {
                    break;
                }
                for(int x : adj[curr]) {
                    if(levels[x] == levels[curr] + 1 && capacity[curr][x] != 0) {
                        found = true;
                        next = x;
                        break;
                    }
                }
                for(int x : transpose[curr]) {
                    if(!found && levels[x] == levels[curr] + 1 && capacity[curr][x] != 0) {
                        found = true;
                        next = x;
                        break;
                    }
                }     
                if(found) {
                    nodes.push(next); 
                } else {
                    levels[curr] = -1;
                    nodes.pop();
                }
            }    
            if(nodes.size()) {
                vector<int> v(nodes.size());
                for(int i = nodes.size() - 1; i >= 0; i--) {
                    v[i] = nodes.top();
                    nodes.pop();
                }
                ll bottleneck = LLONG_MAX;
                for(int i = 1; i < v.size(); i++) {
                    bottleneck = min(bottleneck,capacity[v[i-1]][v[i]]);
                }
                answer += bottleneck;
                for(int i = 1; i < v.size(); i++) {
                    capacity[v[i-1]][v[i]] -= bottleneck;
                    capacity[v[i]][v[i-1]] += bottleneck;
                }       
            } else {
                break;
            }
        }
    }   
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> capacity(n,vector<ll>(n,0));
    vector<vector<ll>> adj(n);
    for(ll i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        adj[--a].push_back(--b);
        capacity[a][b] += c;
    }
    cout << dinic(0,n-1,n,capacity,adj) << "\n";
    return 0;
}