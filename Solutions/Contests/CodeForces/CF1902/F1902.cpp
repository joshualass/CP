#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
//Once you know about the xor basis technique, you can find several ways to solve this problem

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

int basis[200001][20];

//range minimum query. O(1) query, O(n) build/memory. fast.
template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask;
    vector<int> sparse_table;
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int least_significant_bit(int x) {return x & -x;}
    int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
    RMQ() {} //need this to satisfy master goon's requirements
    RMQ (const vector<T>& input) {build(input);}
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
        if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1;
        int y = r / block_size - 1;
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return elements[ans]; //return the value
        // return ans;        //return the index with value
    }
};

//reqs: edges is a valid tree rooted at 0. No cycles.
struct LCA {
    RMQ<int> rmq;
    vector<vector<int>> adj;
    vector<int> ids, nodes, euler, euler_ids, depths;
    int n;
    LCA() {} //default constructor
    //given vector where each node stores its parent
    LCA(const vector<int>& parents) {
        this->n = parents.size() + 1;
        adj.assign(n, {});
        for(int i = 1; i < n; i++) {
            adj[i].push_back(parents[i-1]);
            adj[parents[i-1]].push_back(i);
        }
        build();
    }    

    //given adjacency list. untested
    LCA(const vector<vector<int>> &input_adj) {
        this->n = input_adj.size();
        adj = input_adj;
        build();
    }
    void build() {
        euler_ids.assign(n,-1);
        nodes.assign(n,-1);
        ids.assign(n,-1);
        assign_ids();
        depths.assign(n,-1);
        euler_tour(0,-1,0);
        rmq.build(euler);
    }
    void assign_ids() { // ids assigned in a BFS manner
        queue<pair<int,int>> q; //curr, parent
        int id = 0;
        q.push({0,-1});
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            ids[p.first] = id;
            nodes[id++] = p.first;
            for(auto x : adj[p.first]) if(x != p.second) q.push({x,p.first});  
        }
    }   
    void euler_tour(int i, int p, int d) { 
        euler_ids[i] = euler.size();
        euler.push_back(ids[i]);
        depths[i] = d;
        for(auto x : adj[i]) {
            if(x != p) {
                euler_tour(x,i,d+1);
                euler.push_back(ids[i]);
            }
        }
    }
    //finds lca of node l and r [l,r]
    int lca(int l, int r) { //reverse order
        return nodes[rmq.query(min(euler_ids[l],euler_ids[r]), max(euler_ids[l],euler_ids[r]))];
    }
    int distance(int l, int r) {
        int a = lca(l,r);
        return depths[l] + depths[r] - depths[a] * 2;
    }
};

void assignp(int i, int p, vector<vector<int>> &adj, vector<int> &parents) {
    parents[i] = p;
    for(int c : adj[i]) {
        if(c != p) {
            assignp(c,i,adj,parents);
        }
    }
}

bool insertToBasis(int basisidx, int x) {
    for(int bit = 19; bit >= 0; bit--) {
        if(x & (1 << bit)) {
            if(basis[basisidx][bit]) {
                x ^= basis[basisidx][bit];
            } else {
                basis[basisidx][bit] = x;
                return 1;
            }
        }
    }
    return 0;
}

void dfs(int i, int p, vector<vector<int>> &adj, int x) {
    if(insertToBasis(i,x)) {
        for(int c : adj[i]) {
            if(c != p) {
                dfs(c,i,adj,x);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    memset(basis, 0, sizeof(basis));
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LCA lca(adj);

    // cout << "depths : " << lca.depths << '\n';

    int q; cin >> q;
    vector<vector<array<int,4>>> queries(n);
    vector<vector<int>> atdepth(n);

    for(int i = 0; i < q; i++) {
        int x, y, k; cin >> x >> y >> k;
        x--; y--;
        queries[lca.depths[lca.lca(x,y)]].push_back({x,y,k,i});
    }

    for(int i = 0; i < n; i++) {
        atdepth[lca.depths[i]].push_back(i);
    }

    // cout << "ad : " << atdepth << '\n';

    vector<int> p(n,-1);
    assignp(0,-1,adj,p);

    vector<int> res(q);
    for(int depth = n - 1; depth >= 0; depth--) {
        // cout << "next depth : " << depth << '\n';
        for(int x : atdepth[depth]) {
            // cout << "start dfs add : " << x << " val : " << a[x] << '\n';
            dfs(x, p[x], adj, a[x]);
        }

        for(array<int,4> query : queries[depth]) {

            for(int i = 0; i < 20; i++) {
                basis[200000][i] = basis[query[0]][i];
            }
            for(int i = 0; i < 20; i++) {
                insertToBasis(200000, basis[query[1]][i]);
            }
            if(!insertToBasis(200000, query[2])) {
                // cout << "query : " << query << " is ok!\n";
                // cout << "print basis bruh\n";
                // for(int i = 19; i >= 0; i--) {
                //     cout << basis[200000][i] << " ";
                // }
                // cout << '\n';
                res[query[3]] = 1;
            }
        }
    }

    for(int q : res) {
        cout << (q ? "Yes" : "No") << '\n';
    }

    return 0;
}