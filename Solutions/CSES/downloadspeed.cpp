#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
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
*/

template<class T>
T edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vector<int> par(graph.size());
    vector<int> q = par;

    for(;;) {
        fill(par.begin(), par.end(), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        for(int i = 0; i < ptr; i++) {
            int x = q[i];
            for(auto e : graph[x]) {
                if(par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if(e.first == sink) goto out;
                }
            }
        }
    return flow;
out:
    T inc = numeric_limits<T>::max();
    for(int y = sink; y != source; y = par[y]) {
        inc = min(inc, graph[par[y]][y]);
    }

    flow += inc;
    for(int y = sink; y != source; y = par[y]) {
        int p = par[y];
        if((graph[p][y] -= inc) <= 0) {
            graph[p].erase(y);
        }
        graph[y][p] += inc;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<unordered_map<int,ll>> graph(n);

    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--;
        b--;
        graph[a][b] += c;
    }

    cout << edmondsKarp(graph,0,n-1) << '\n';

    return 0;
}