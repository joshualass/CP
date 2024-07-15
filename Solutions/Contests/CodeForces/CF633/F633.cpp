#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// {distance, a}
array<ll,2> dfs(int i, int p, ll d, vector<vector<int>> &adj, vector<ll> &weights, int evil) {
    array<ll,2> res = {d, i};
    for(int c : adj[i]) {
        if(c != p && c != evil) {
            res = max(res, dfs(c,i,d+weights[c],adj, weights, evil));
        }
    }
    return res;
}

//{a, b, diameter}
array<ll,3> find_diameter(vector<vector<int>> &adj, vector<ll> &weights, int start = 0, int evil = -1) {
    array<ll,2> a = dfs(start,-1,weights[start],adj, weights, evil);
    array<ll,2> b = dfs(a[1],-1,weights[a[1]],adj, weights, evil);
    return {a[1], b[1], b[0]};
}

bool find_path(int i, int p, int dest, vector<vector<int>> &adj, vector<int> &path) {
    if(i == dest) {
        path.push_back(i);
        return 1;
    }

    for(int c : adj[i]) {
        if(c != p) {
            if(find_path(c,i,dest,adj,path)) {
                path.push_back(i);
                return 1;
            }
        }
    }

    return 0;
}

void get_dists(int i, int p, ll d, vector<vector<int>> &adj, vector<ll> &a, vector<ll> &dists) {

    dists[i] = d;
    for(int c : adj[i]) {
        if(c != p) {
            get_dists(c,i,d + a[c], adj, a, dists);
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll& x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    array<ll,3> diameter = find_diameter(adj, a);

    vector<int> path;
    find_path(diameter[0], -1, diameter[1], adj, path);
    reverse(path.begin(), path.end());

    vector<ll> da(n);
    vector<ll> db(n);
    get_dists(diameter[0], -1, a[diameter[0]], adj, a, da);
    get_dists(diameter[1], -1, a[diameter[1]], adj, a, db);

    vector<ll> maxsubs(path.size());
    ll maxgreen = 0;
    for(int i = 0; i < path.size(); i++) {
        for(int c : adj[path[i]]) {
            if((i == 0 || i != 0 && c != path[i-1]) && (i == path.size() - 1 || i != path.size() - 1 && c != path[i+1])) {
                maxsubs[i] = max(maxsubs[i], dfs(c,path[i],a[c],adj,a,-1)[0]);
                // cout << "c : " << c << " mag : " << find_diameter(adj,a,c,path[i])[2] << '\n';
                maxgreen = max(maxgreen, find_diameter(adj,a,c,path[i])[2]);
            }
        }
    }

    // cout << "diameter : " << diameter << '\n';
    // cout << "path : " << path << '\n';
    // cout << "maxsubs : " << maxsubs << '\n';

    vector<ll> aftermaxes(path.size());
    
    for(int i = path.size() - 1; i >= 0; i--) {
        if(i != path.size() - 1) {
            aftermaxes[i] = aftermaxes[i+1];
        }

        aftermaxes[i] = max(aftermaxes[i], maxsubs[i] + db[path[i]]);

    }

    // cout << "aftermath : " << aftermaxes << '\n';

    ll res = 0;

    for(int i = 0; i < path.size() - 1; i++) {
        // cout << "i : " << i << " path[i] : " << path[i] << " would be val : " << da[path[i]] + maxsubs[i] + aftermaxes[i+1] << '\n';
        res = max(res, da[path[i]] + maxsubs[i] + aftermaxes[i+1]);
    }

    //also should handle if it is a green path - no intersection with the diagonal
    
    // cout << "mag : " << maxgreen << '\n';


    cout << max(res, aftermaxes[0] + maxgreen) << '\n';

    return 0;
}