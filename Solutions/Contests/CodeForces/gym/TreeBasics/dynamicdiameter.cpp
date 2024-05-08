#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

pair<int,int> dfs1(int i, int d, int p, vector<vector<int>> &adj) {
    pair<int,int> res = {i,d};
    for(int c : adj[i]) {
        if(c != p) {
            pair<int,int> a = dfs1(c,d+1,i,adj);
            if(a.second > res.second) {
                res = a;
            }
        }
    }
    return res;
}

void get_dists(int i, int p, int d, vector<vector<int>> &adj, vector<int> &dists) {
    dists[i] = d;
    for(int c : adj[i]) {
        if(c != p) {
            get_dists(c,i,d+1,adj,dists);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    pair<int,int> farthest = dfs1(0,0,-1,adj);
    pair<int,int> farthest2 = dfs1(farthest.first, 0, -1, adj);

    // cout << "f1 : " << farthest << '\n';
    // cout << "f2 : " << farthest2 << '\n';

    vector<int> d1(n);
    vector<int> d2(n);
    get_dists(farthest.first, -1, 0, adj,d1);
    get_dists(farthest2.first, -1, 0, adj,d2);

    // cout << "d1 : " << d1 << '\n';
    // cout << "d2 : " << d2 << '\n';

    pair<int,vector<int>> centers = {INT_MAX,{}};
    for(int i = 0; i < n; i++) {
        if(max(d1[i],d2[i]) < centers.first) {
            centers = {max(d1[i],d2[i]), {i}};
        } else if(max(d1[i],d2[i]) == centers.first) {
            centers.second.push_back(i);
        }
    }

    queue<pair<int,int>> q;
    vector<int> dists(n,-1);
    for(int x : centers.second) {
        q.push({x,0});
    }
    int maxd = -1;
    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        if(dists[p.first] != -1) continue;
        dists[p.first] = p.second;
        maxd = p.second;
        for(int x : adj[p.first]) {
            q.push({x,p.second+1});
        }
    }

    // cout << "centers : " << centers.second << '\n';
    // cout << "dists : " << dists << '\n';

    for(int i = 0; i < n; i++) {
        cout << farthest2.second + (dists[i] == maxd) << '\n';
    }

    return 0;
}