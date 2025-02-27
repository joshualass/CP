#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
it is sufficient for dfs to work if it's possible for each node to appear after the node before it
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

void updatestatus(int i, vector<int> &perm, LCA &lca, int &status, vector<int> &statuses, vector<int> &p, vector<int> &isleaf) {

    bool ok = 1;
    int node = perm[i];

    if(i == 0 || perm[i] == 0) {
        if(i != 0 || perm[i] != 0) {
            ok = 0;
        }
    } else {
        int par = p[node-1];
        if(perm[i-1] != par) {
            int node2 = perm[i-1];
            if(!isleaf[node2] || lca.lca(node,node2) != par) {
                // cout << "i : " << i << " node : " << node << " par : " << par << " node2 : " << node2 << '\n';
                ok = 0;
            }
        }
    }

    if(ok) {
        if(!statuses[node]) {
            statuses[node] = 1;
            status++;
        }
    } else {
        if(statuses[node]) {
            statuses[node] = 0;
            status--;
        }
    }

}

void solve() {
    
    int n, q; cin >> n >> q;
   
    vector<int> p(n-1);
    vector<int> isleaf(n,1);
    for(int &x : p) {
        cin >> x;
        x--;
        isleaf[x] = 0;
    }

    vector<int> perm(n);
    for(int i = 0; i < n; i++) {
        cin >> perm[i];
        perm[i]--;
    }

    LCA lca(p);

    int status = 0;
    vector<int> statuses(n);
    for(int i = 0; i < n; i++) {
        updatestatus(i,perm,lca,status,statuses,p,isleaf);
    }

    // cout << "statuses start : " << statuses << '\n';

    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        swap(perm[x],perm[y]);
        updatestatus(x,perm,lca,status,statuses,p,isleaf);
        updatestatus(min(x+1,n-1),perm,lca,status,statuses,p,isleaf);
        updatestatus(y,perm,lca,status,statuses,p,isleaf);
        updatestatus(min(y+1,n-1),perm,lca,status,statuses,p,isleaf);

        // cout << "perm : " << perm << "\n";
        // cout << "status : " << status << '\n';

        cout << (status == n ? "Yes" : "No") << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}