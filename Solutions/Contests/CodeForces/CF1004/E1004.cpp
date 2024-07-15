#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

// {distance, a}
array<int,2> dfs(int i, int p, int d, vector<vector<array<int,2>>> &adj) {
    array<int,2> res = {d, i};
    for(array<int,2> c : adj[i]) {
        if(c[0] != p) {
            res = max(res, dfs(c[0],i,d + c[1],adj));
        }
    }
    return res;
}

//{a, b, diameter}
array<int,3> find_diameter(vector<vector<array<int,2>>> &adj) {
    array<int,2> a = dfs(0,-1,0,adj);
    array<int,2> b = dfs(a[1],-1,0,adj);
    return {a[1], b[1], b[0]};
}

bool find_path(int i, int p, int dest, vector<vector<array<int,2>>> &adj, vector<int> &path) {
    if(i == dest) {
        path.push_back(i);
        return 1;
    }
    
    for(array<int,2> c : adj[i]) {
        if(c[0] != p) {
            if(find_path(c[0],i,dest,adj,path)) {
                path.push_back(i);
                return 1;
            }
        }
    }
    return 0;
}

void find_dist(int i, int p, int d, vector<vector<array<int,2>>> &adj, vector<int> &dist) {
    dist[i] = d;
    for(array<int,2> c : adj[i]) {
        if(c[0] != p) {
            find_dist(c[0], i, d + c[1], adj, dist);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    vector<vector<array<int,2>>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    array<int,3> diameter = find_diameter(adj);

    vector<int> path;
    find_path(diameter[0], -1, diameter[1], adj, path);

    set<int> inpath(path.begin(), path.end());

    // cout << "diameter : " << diameter << '\n';
    // cout << "path : " << path << '\n';

    vector<int> dista(n), distb(n);
    find_dist(diameter[0],-1,0,adj,dista);
    find_dist(diameter[1],-1,0,adj,distb);

    // cout << "da : " << dista << '\n';
    // cout << "db : " << distb << '\n';

    Tree<int> tree(path.size());
    for(int i = 0; i < path.size(); i++) {
        array<int,2> furthest = {0,0};
        for(array<int,2> c : adj[path[i]]) {
            if(inpath.count(c[0]) == 0) {
                furthest = max(furthest, dfs(c[0], path[i], c[1], adj));
            }
        }
        tree.update(i,furthest[0]);
    }

    int best = INT_MAX;
    if(k >= path.size()) {
        best = tree.query(0,path.size());
    } else {

        for(int i = 0; i + k <= path.size(); i++) {
            // cout << "i : " << i << " path[i] : " << path[i] << " da : " << distb[path[i]] << " tree part : " << tree.query(i,i+k) << " db : " << dista[path[i+k-1]] << '\n';
            best = min(best, max({distb[path[i]], tree.query(i,i+k), dista[path[i+k-1]]}));
        }

    }

    cout << best << '\n';

    return 0;
}