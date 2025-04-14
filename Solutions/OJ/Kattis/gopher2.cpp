// C++ Program For Ford Fulkerson Algorithm
#include <bits/stdc++.h>
typedef long double ld;
typedef long long ll;
using namespace std;

void printV(vector<int> &x) {
    for(int y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void printAdj(const vector<vector<ll>> &adj) {
    cout << " --- adjlist --- \n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i - " << i << ':';
        for(ll x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

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

    // freopen("gopherii.in","r",stdin);

    int n, m, s, v; cin >> n >> m >> s >> v;
    while(!cin.eof()) {
        int N = n + m + 2;
        vector<pair<ld,ld>> gophers(n);
        vector<pair<ld,ld>> holes(m);
        for(int i = 0; i < n; i++) {
            cin >> gophers[i].first;
            cin >> gophers[i].second;
        }
        for(int i = 0; i < m; i++) {
            cin >> holes[i].first;
            cin >> holes[i].second;
        }
        // vector<vector<int>> graph(N, vector<int>(N,0));
        vector<vector<ll>> adj(N);
        vector<vector<ll>> capacity(N,vector<ll>(N));
        ld distance = s * v;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ld dist = sqrt((gophers[i].first - holes[j].first) * (gophers[i].first - holes[j].first) + (gophers[i].second - holes[j].second)*(gophers[i].second - holes[j].second));
                if(dist <= distance + 0.000001) {
                    adj[i].push_back(n + j);
                    capacity[i][n+j]++;
                }
            }
        }
        for(int i = 0; i < n; i++) {
            adj[n + m].push_back(i);
            capacity[n + m][i]++;
        }
        for(int i = 0; i < m; i++) {
            adj[n + i].push_back(N-1);
            capacity[n + i][N-1]++;
        }
        // printAdj(adj);
        // printAdj(capacity);
        int gophahs2 = dinic(n + m, n + m + 1, N, capacity, adj);
        cout << n - gophahs2 << "\n";
        cin >> n >> m >> s >> v;
    }
}