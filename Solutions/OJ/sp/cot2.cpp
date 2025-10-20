#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;
const int SQN = 282;

#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

/*
this code TLEs 
and im not very interested in optimizing ...
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
const int MAXN = 40000;
vector<vector<int>> adj;
int a[MAXN], in[MAXN], out[MAXN], attime[MAXN * 2];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    adj.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> s;
    for(int i = 0; i < n; i++) s.insert(a[i]);
    map<int,int> cm;
    int p = 0;
    for(int x : s) cm[x] = p++;
    for(int &x : a) x = cm[x];

    // cout << "a : " << a << '\n';

    vector<int> in(n), out(n);
    vector<int> attime;
    int time = 0;
    auto dfs = [&](auto self, int i, int p) -> void {
        attime[time] = i;
        in[i] = time++;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
        attime[time] = i;
        out[i] = time++;
    };

    dfs(dfs, 0, -1);

    // cout << "in : " << in << '\n';
    // cout << "out : " << out << '\n';
    // cout << "att : " << attime << '\n';

    //atbucket[i] stores the bucket each index is in
    vector<int> atbucket;
    int cur_bucket = 0, sz = 0;

    for(int i = 0; i < n * 2; i++) {
        if(sz + 1 > SQN) {
            cur_bucket++;
            sz = 1;
        }
        atbucket.push_back(cur_bucket);
    }

    int bc = cur_bucket + 1;
    LCA lca(adj);

    //[l][r] => vector of tuples of the form {true l, true r, query id}
    vector<vector<vector<array<int,3>>>> queries(bc, vector<vector<array<int,3>>>(bc));
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        //ensure we visit node l first
        if(in[l] > in[r]) swap(l, r);
        int anc = lca.lca(l, r);
        int lidx, ridx;
        //case one is not the parent of the other. 
        if(anc != l && anc != r) {
            lidx = out[l];
            ridx = in[r];
        } else {
            lidx = in[l];
            ridx = in[r];
        }
        int lb = atbucket[lidx], rb = atbucket[ridx];
        queries[lb][rb].push_back({lidx, ridx, i});
    }

    vector<int> cnts_value(p), cnts_node(n);
    int cur = 0;

    // auto toggle = [&](int idx) -> void {
    //     int node = attime[idx];
    //     int val = a[node];

    //     cur -= cnts_value[val] > 0;
    //     if(cnts_node[node] == 0) {
    //         cnts_value[val]++;
    //     } else {
    //         cnts_value[val]--;
    //     }
    //     cnts_node[node] ^= 1;

    //     cur += cnts_value[val] > 0;
    // };

    // auto toggle = [&](int idx) {
    //     int node = attime[idx];
    //     int val  = a[node];

    //     int before = (cnts_value[val] != 0);
    //     if (cnts_node[node] == 0) ++cnts_value[val];
    //     else                      --cnts_value[val];
    //     cnts_node[node] ^= 1;
    //     int after  = (cnts_value[val] != 0);

    //     cur += (after - before);
    // };

    auto toggle = [&](int idx) {
        int node = attime[idx];
        if(cnts_node[node] && (--cnts_value[a[node]] == 0)) cur--;
        if(!cnts_node[node] && (cnts_value[a[node]]++ == 0)) cur++;
        cnts_node[node] ^= 1;  
    };

    vector<int> res(m);
    int curl = 0, curr = -1;

    auto handle_queries = [&](int i, int j) -> void {
        for(auto [l, r, id] : queries[i][j]) {
            while(curl > l) {
                toggle(--curl);
            }
            while(curr < r) {
                toggle(++curr);
            }
            while(curl < l) {
                toggle(curl++);
            }
            while(curr > r) {
                toggle(curr--);
            }
            
            int lnode = attime[l], rnode = attime[r];
            int anc = lca.lca(lnode, rnode);
            
            if(anc != lnode && anc != rnode) {
                toggle(in[anc]);
            }
            
            // cout << "l : " << l << " r : " << r << " id : " << id << '\n';
            // cout << "node states : " << cnts_node << '\n';
            res[id] = cur;

            if(anc != lnode && anc != rnode) {
                toggle(in[anc]);
            }
        }
    };


    for(int i = 0; i < bc; i++) {
        if(i % 2 == 0) {
            for(int j = i; j < bc; j++) {
                handle_queries(i, j);
            }
        } else {
            for(int j = bc - 1; j >= i; j--) {
                handle_queries(i, j);
            }
        }
    }

    for(int i = 0; i < m; i++) cout << res[i] << "\n";

    return 0;
}
