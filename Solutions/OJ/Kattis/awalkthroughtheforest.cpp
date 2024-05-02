#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto x : adj) {
//         for(auto y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//minimal side effect topological sort
void _topological(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &ans) {
    // cout << "top sort: " << i << '\n';
    visited[i] = true;
    for(auto x : adj[i]) {
        if(!visited[x]) {
            _topological(x,adj,visited,ans);
        }
    }
    ans.push_back(i);
}

vector<int> topological_sort(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n);
    vector<int> ans;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            _topological(i, adj, visited, ans);
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n>> m;
    while(n != 0) {
        vector<set<pair<int,int>>> adj(n);
        for(int i = 0; i < m; i++) {
            int a, b, d; cin >> a >> b >> d;
            a--; b--;
            adj[a].insert({b,d});
            adj[b].insert({a,d});
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,1});
        vector<int> mintime(n,-1);
        while(pq.size()) {
            pair<int,int> p = pq.top();
            pq.pop();
            if(mintime[p.second] != -1) continue;
            mintime[p.second] = p.first;
            for(pair<int,int> to : adj[p.second]) {
                if(mintime[to.first] == -1) {
                    pq.push({p.first + to.second, to.first});
                }
            }
        }
        // cout << "mintimes : " << mintime << '\n';
        for(int i = 0; i < n; i++) {
            vector<pair<int,int>> kill;
            for(pair<int,int> edge : adj[i]) {
                if(mintime[edge.first] >= mintime[i]) {
                    kill.push_back(edge);
                }
            }
            for(auto edge : kill) {
                adj[i].erase(edge);
            }
        }
        vector<vector<int>> uadj(n);
        for(int i = 0; i < n; i++) {
            for(auto edge : adj[i]) {
                uadj[i].push_back(edge.first);
            }
        }

        // cout << "uadj\n" << uadj;


        vector<int> topo = topological_sort(uadj);
        vector<int> paths(n);
        paths[0] = 1;
        for(int x : topo) {
            for(int to : uadj[x]) {
                paths[to] += paths[x];
            }
        }
        cout << paths[1] << '\n';
        cin >> n >> m;
    }

    return 0;
}