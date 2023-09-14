#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int m, n;
int c, d;
vector<vector<int>> adj;
vector<vector<int>> trans;
vector<pair<int,int>> order; 
vector<bool> visited;
stack<int> s;

void DFS(int index) {
    visited[index] = true;
    for(int x : adj[index]) {
        if(!visited[x]) {
            if(index == c && x == d) {
                continue;
            }
            DFS(x);
        }
    }
    if(index == d) {
        if(!visited[c]) {
            DFS(c);
        }
    }
    s.push(index);
}

int DFS2(int index) {
    visited[index] = true;
    int total = 1;
    for(int x : trans[index]) {
        if(!visited[x]) {
            if(index == d && x == c) {
                continue;
            }
            total += DFS2(x);
        }
    }
    if(index == c) {
        if(!visited[d]) {
            total += DFS2(d);
        }
    }
    return total;
}

bool solve() {
    visited.assign(m,false);
    while(s.size()) {
        s.pop();
    }
    for(int i = 0; i < m; i++) {
        if(!visited[i]) {
            DFS(i);
        }
    }
    visited.assign(m,false);
    return DFS2(s.top()) == m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // freopen("reversingroads.in","r",stdin);
    int casi = 0;
    cin >> m >> n; //m nodes n edges
    while(!cin.eof() && cin.good()) {
        // cout << "m: " << m << " n: " << n << "\n";
        adj.assign(m,{});
        trans.assign(m,{});
        order.clear();
        c = -1; d = -1;
        for(int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            trans[b].push_back(a);
            order.push_back({a,b});
        }
        cout << "Case " << ++casi << ": ";
        bool found = false;
        if(solve()) {
            cout << "valid";
            found = true;
        }
        for(int i = 0; i < order.size() && !found; i++) {
            c = order[i].first;
            d = order[i].second;
            if(solve()) {
                cout << c << " " << d;
                found = true; 
            }  
        }

        
        cout << (found ? "" : "invalid") << "\n";
        cin >> m >> n; //m nodes n edges
    }

    return 0;
}