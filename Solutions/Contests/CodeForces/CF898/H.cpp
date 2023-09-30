#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<bool> &x) {
    cout << " --- vector --- ";
    for(auto y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void printV2(const vector<int> &x) {
    cout << " --- vector --- ";
    for(auto y : x) {
        cout << y << " ";
    }
    cout << "\n";
}


void dfs(int i, int p, vector<bool> &cycle, vector<int> &visited, vector<vector<int>> &adj) {
    if(cycle[i]) return;
    // cout << "i: " << i << " p: " << p << "\n";
    // printV2(visited);
    if(visited[i] != -1) {
        cycle[i] = true;
        // cout << "i true: " << i << "\n";
        p = visited[i];
        while(p != i) {
            // cout << "p true: " << p << "\n";
            cycle[p] = true;
            p = visited[p];
        }
        return;
    }
    // visited[i] = p;
    for(auto x : adj[i]) {
        if(x != p) {
            visited[i] = x;
            dfs(x,i,cycle,visited,adj);
        }
    }

}

void solve() {
    int n, a, b; cin >> n >> a >> b;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++) {
        int c,d; cin >> c >> d;
        c--; d--;
        adj[c].push_back(d);
        adj[d].push_back(c);
    }
    vector<bool> cycle(n);
    vector<int> visited(n,-1);
    dfs(0,-1,cycle,visited,adj);
    // printV(cycle);
    vector<int> hunter(n,-1);
    queue<pair<int,int>> q;
    q.push({--a,0});
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        if(hunter[p.first] == -1) {
            hunter[p.first] = p.second;
            for(auto x : adj[p.first]) {
                q.push({x,p.second+1});
            }
        }
    }
    // printV2(hunter);
    bool evaded = false;
    q.push({--b,0});
    vector<bool> visitation(n);
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        if(!visitation[p.first]) {
            visitation[p.first] = true;
            if(cycle[p.first] && p.second < hunter[p.first]) {
                evaded = true;
            }
            for(auto x : adj[p.first]) {
                q.push({x,p.second+1});
            }
        }
    }
    cout << (evaded ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}