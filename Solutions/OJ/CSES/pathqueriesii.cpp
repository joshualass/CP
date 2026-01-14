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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a,b);
//     }
//     Tree(int n, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, tout, depths, par, heads, starts;
    //heads[i] => for node i, the node with least depth that contains node i in its heavy path
    //starts[i] => where in contiguous memory this point is. 

    HLD(vector<vector<int>> adj) {
        this->adj = adj;
        build();
    }

    void build() {
        this->n = adj.size();
        tin.assign(n, -1);
        tout.assign(n, -1);
        depths.assign(n, -1);
        par.assign(n, -1);

        int time = 0;

        auto euler = [&](auto self, int i, int p, int d) -> void {
            tin[i] = time++;
            depths[i] = d;
            par[i] = p;
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, d + 1);
                }
            }
            tout[i] = time;
        };

        euler(euler, 0, -1, 0);

        heads.assign(n, -1);
        starts.assign(n, -1);

        time = 0;
        auto hld = [&](auto self, int i, int p, int head) -> void {
            if(head == -1) {
                head = i;
            }

            heads[i] = head;
            starts[i] = time++;

            int hc = -1;
            for(int c : adj[i]) {
                if(c != p) {
                    if(hc == -1 || tout[c] - tin[c] > tout[hc] - tin[hc]) {
                        hc = c;
                    }
                }
            }

            if(hc == -1) return;

            self(self, hc, i, head);
            for(int c : adj[i]) {
                if(c != p && c != hc) {
                    self(self, c, i, -1);
                }
            }
        };

        hld(hld, 0, -1, -1);

        // cout << "tin : " << tin << '\n';
        // cout << "tout : " << tout << '\n';
        // cout << "depths : " << depths << '\n';
        // cout << "par : " << par << '\n';
        // cout << "heads : " << heads << '\n';
        // cout << "starts : " << starts << '\n';

    }

    int lca(int a, int b) {
        while(heads[a] != heads[b]) {
            if(depths[heads[a]] > depths[heads[b]]) {
                a = par[heads[a]];
            } else {
                b = par[heads[b]];
            }
        }
        if(depths[a] < depths[b]) {
            return a;
        } else {
            return b;
        }
    }

    //lca + dist work, see https://cses.fi/problemset/result/15390705/
    int dist(int a, int b) {
        int unc = lca(a, b);
        return depths[b] + depths[a] - depths[unc] * 2;
    }

    vector<array<int,2>> path(int a, int b) {
        vector<array<int,2>> res;

        auto append_path = [&](int cur, int depth) -> void {
            if(depths[cur] < depth) return;
            while(1) {
                if(depths[heads[cur]] <= depth) {
                    res.push_back({starts[heads[cur]] + (depth - depths[heads[cur]]), starts[cur] + 1});
                    break;
                }
                res.push_back({starts[heads[cur]], starts[cur] + 1});
                cur = par[heads[cur]];
            }
        };

        int unc = lca(a, b);
        int unc_depth = depths[unc];

        append_path(a, unc_depth);
        int sz = res.size();
        append_path(b, unc_depth + 1);
        reverse(res.begin() + sz, res.end());
        return res;
    }

    // int query(int a, int b, Tree &tree) {
    //     int res = 0;

    //     auto append_path = [&](int cur, int depth) -> void {
    //         if(depths[cur] < depth) return;
    //         while(1) {
    //             if(depths[heads[cur]] <= depth) {
    //                 res = tree.f(res, tree.query(starts[heads[cur]] + (depth - depths[heads[cur]]), starts[cur] + 1));
    //                 break;
    //             }
    //             res = tree.f(res, tree.query(starts[heads[cur]], starts[cur] + 1));
    //             cur = par[heads[cur]];
    //         }
    //     };

    //     int unc = lca(a, b);
    //     int unc_depth = depths[unc];

    //     append_path(a, unc_depth);
    //     append_path(b, unc_depth + 1);
    //     return res;
    // }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD hld(adj);

    Tree tree(n);
    for(int i = 0; i < n; i++) tree.update(hld.starts[i], a[i]);

    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int s, x; cin >> s >> x;
            s--;
            tree.update(hld.starts[s], x);
        } else {
            int u, v; cin >> u >> v;
            u--; v--;
            cout << hld.query(u, v, tree) << " ";
            // auto path = hld.path(u, v);
            // int res = tree.base;
            // for(auto [l, r] : path) res = tree.f(res, tree.query(l,r));
            // cout << res << " ";
        }
    }

    cout << '\n';

    //distance queries 
    // int n, q; cin >> n >> q;
    // vector<vector<int>> adj(n);
    // for(int i = 1; i < n; i++) {
    //     int u, v; cin >> u >> v;
    //     u--; v--;
    //     adj[u].push_back(v);
    //     adj[v].push_back(u);
    // }

    // Tree tree(adj);

    // for(int qq = 0; qq < q; qq++) {
    //     int u, v; cin >> u >> v;
    //     u--; v--;
    //     cout << tree.dist(u, v) << '\n';
    // }

    return 0;
}


// #pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// //range minimum query. O(1) query, O(n) build/memory. fast.
// template<typename T>
// struct RMQ  {
//     vector<T> elements;
//     int n;
//     static const int block_size = 30; // block size. adjust accordingly
//     vector<int> mask;
//     vector<int> sparse_table;
//     int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
//         return elements[x] < elements[y] ? x : y;
//     }
//     int least_significant_bit(int x) {return x & -x;}
//     int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
//     int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
//     RMQ() {} //need this to satisfy master goon's requirements
//     RMQ (const vector<T>& input) {build(input);}
//     void build (const vector<T>& input) {
//         elements = input;
//         n = input.size();
//         mask.assign(n,0);
//         sparse_table.assign(n,0);
//         int curr_mask = 0;
//         for(int i = 0; i < n; i++) {
//             curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
//             while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
//             curr_mask |= 1;
//             mask[i] = curr_mask;
//         }
//         for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
//         for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
//     }
//     T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
//         if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
//         int ans = op(small_query(l + block_size - 1), small_query(r)); 
//         int x = l / block_size + 1;
//         int y = r / block_size - 1;
//         if(x <= y) {
//             int j = most_significant_bit_index(y - x + 1);
//             ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
//         }
//         return elements[ans]; //return the value
//         // return ans;        //return the index with value
//     }
// };

// //reqs: edges is a valid tree rooted at 0. No cycles.
// // template<typename T>
// struct LCA {
//     RMQ<int> rmq;
//     vector<vector<int>> adj;
//     vector<int> ids; //stores id of node at i
//     vector<int> nodes; //stores node of id at i
//     vector<int> euler;
//     vector<int> euler_ids;
//     int n;
//     LCA() {} //default constructor
//     //given vector where each node stores its parent
//     LCA(const vector<int>& parents) {
//         this->n = parents.size() + 1;
//         adj.assign(n, {});
//         for(int i = 1; i < n; i++) {
//             adj[i].push_back(parents[i-1]);
//             adj[parents[i-1]].push_back(i);
//         }
//         build();
//     }    

//     //given adjacency list. untested
//     LCA(const vector<vector<int>> &input_adj) {
//         this->n = input_adj.size();
//         adj = input_adj;
//         build();
//     }
//     void build() {
//         euler_ids.assign(n,-1);
//         nodes.assign(n,-1);
//         ids.assign(n,-1);
//         assign_ids();
//         euler_tour(0,-1);
//         rmq.build(euler);
//     }
//     void assign_ids() {
//         queue<pair<int,int>> q; //curr, parent
//         int id = 0;
//         q.push({0,-1});
//         while(q.size()) {
//             pair<int,int> p = q.front();
//             q.pop();
//             ids[p.first] = id;
//             nodes[id++] = p.first;
//             for(auto x : adj[p.first]) if(x != p.second) q.push({x,p.first});  
//         }
//     }   
//     void euler_tour(int i, int p) {
//         euler_ids[i] = euler.size();
//         euler.push_back(ids[i]);
//         for(auto x : adj[i]) {
//             if(x != p) {
//                 euler_tour(x,i);
//                 euler.push_back(ids[i]);
//             }
//         }
//     }
//     //finds lca of node l and r [l,r]
//     int find_lca(int l, int r) { //reverse order
//         return nodes[rmq.query(min(euler_ids[l],euler_ids[r]), max(euler_ids[l],euler_ids[r]))];
//     }
// };

// template<typename T>
// struct Lazy {
//     static constexpr T ln = 0, qn = 0; //stores the starting values at all nodes, 
//     vector<T> v;      //stores values at each index we are querying for
//     vector<T> lazy;   //stores lazy updates at each node
//     vector<bool> upd; //stores at each node, whether there is a lazy update to push
//     int n, size;
//     Lazy(int n = 0, T def = qn) {
//         build(n,def);
//     }
//     void build(int n = 0, T def = qn) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//         lazy.assign(size * 2, ln);
//         upd.assign(size * 2, 0);
//     }
//     bool isLeaf(int node) {
//         return node >= size;
//     }
//     T query_comb(T val1, T val2) {//update this depending on query type
//         return max(val1, val2);
//     }
//     //how we combine lazy updates to lazy
//     void lazy_comb(int node, T val) {//update this depending on update type. how do we merge the lazy changes?
//         lazy[node] = val;
//         upd[node] = 1;
//     }
//     void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
//         v[node] = lazy[node];
//     }
//     void push_lazy(int node, int size) {
//         main_comb(node, size); //push lazy change to current node
//         if(!isLeaf(node)) {
//             lazy_comb(node * 2, lazy[node]);
//             lazy_comb(node * 2 + 1, lazy[node]);
//             upd[node * 2] = 1;
//             upd[node * 2 + 1] = 1;
//         }
//         lazy[node] = ln;
//         upd[node] = 0;
//     }
//     void update(int l, int r, T val) {
//         _update(1,0,size,l,r,val);
//     }
//     void _update(int node, int currl, int currr, int &targetl, int &targetr, T &val) {
//         if(upd[node]) {
//             push_lazy(node,currr-currl);
//         }
//         if (currl >= targetr || currr <= targetl) { //there is no overlap
//             return; //do nothing if there is no overlap
//         }
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
//             push_lazy(node, currr-currl);
//         } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
//             int mid = (currl + currr) / 2;
//             _update(node * 2, currl, mid, targetl, targetr, val);
//             _update(node * 2 + 1, mid, currr, targetl, targetr, val);
//             v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
//         }
//     }
//     T query(int l, int r) {
//         return _query(1,0,size,l,r);
//     }
//     T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
//         if(currr <= targetl || currl >= targetr) { //no overlap
//             return qn; 
//         } 
//         if(upd[node]) push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             return v[node];
//         } else {
//             int mid = (currl + currr) / 2;
//             return query_comb(
//                 _query(node * 2, currl, mid, targetl, targetr),
//                 _query(node * 2 + 1, mid, currr, targetl, targetr)
//             );
//         }
//     }
// };

// template <typename T>
// struct HLD {
//     int n;
//     int id = 0;
//     bool nodemode;
//     vector<vector<int>> adj;
//     vector<int> parents;
//     vector<int> ids; //stores id of node at i
//     vector<int> nodes; //stores node of id at i
//     vector<int> euler; //do not assign this vector
//     vector<int> euler_ids;
//     vector<int> lazyidxs; //for node i, which lazy segtree it is in
//     vector<int> heavypathidxs; //for node i, which heavy path it is in
//     vector<int> heavyheads; //the node which is the head for heavy path at index i
//     vector<int> heavytails; //the node which is the tail for heavy path at index i
//     vector<int> subtree_sizes;
//     Lazy<T> lazy;
//     RMQ<int> rmq;
//     vector<T> plazy; //precompute some of the heavy paths such that the query is logn
//     HLD() {} //default constructor
//     HLD(const vector<vector<int>> &input_adj, vector<T> &w, bool nodemode) {
//         build(input_adj,w,nodemode);
//     }
//     //build data structure
//     void build(const vector<vector<int>> &adj, vector<T> &w, bool nodemode) {
//         //resize everything
//         this->n = adj.size();
//         this->nodemode = nodemode;
//         this->adj = adj;
//         parents.assign(n,-1);
//         ids.assign(n,-1);
//         nodes.assign(n,-1);
//         euler_ids.assign(n,-1);
//         lazyidxs.assign(n,-1);
//         heavypathidxs.assign(n,-1);
//         subtree_sizes.assign(n,-1);
//         lazy.build(n);  
//         //populate the data structure 
//         build_LCA();
//         build_heavy(w);
//     }
//     void build_LCA() {
//         assign_ids();
//         euler_tour(0,-1);
//         rmq.build(euler);
//     }
//     void build_heavy(vector<T> &w) {
//         heavyheads.push_back(0);
//         heavy_dfs(0,-1,w);
//         plazy.assign(heavyheads.size(), 0);
//         for(int i = 0; i < heavyheads.size(); i++) {
//             plazy[i] = lazy.query(lazyidxs[heavyheads[i]], lazyidxs[heavytails[i]] + 1);
//         }
//     }
//     void assign_ids() {
//         queue<pair<int,int>> q; //curr, parent
//         int id = 0;
//         q.push({0,-1});
//         while(q.size()) {
//             pair<int,int> p = q.front();
//             q.pop();
//             ids[p.first] = id;
//             nodes[id++] = p.first;
//             for(auto x : adj[p.first]) if(x != p.second) q.push({x,p.first});  
//         }
//     }   
//     int euler_tour(int i, int p) {
//         int size = 1;
//         euler_ids[i] = euler.size();
//         euler.push_back(ids[i]);
//         parents[i] = p;
//         for(auto x : adj[i]) {
//             if(x != p) {
//                 size += euler_tour(x,i);
//                 euler.push_back(ids[i]);
//             }
//         }
//         subtree_sizes[i] = size;
//         return size;
//     }
//     void heavy_dfs(int i, int p, vector<T> &w) {
//         lazyidxs[i] = id;
//         lazy.update(id,id+1,w[i]);
//         id++;
//         heavypathidxs[i] = heavyheads.size() - 1;
//         int lidx = -1;
//         for(int c : adj[i]) {
//             if(c != p) {
//                 if(lidx == -1 || subtree_sizes[c] > subtree_sizes[lidx]) {
//                     lidx = c;
//                 }
//             }
//         }
//         if(lidx != -1) {
//             heavy_dfs(lidx,i,w);
//         } else {
//             heavytails.push_back(i);
//         }
        
//         for(int c : adj[i]) {
//             if(c != p && c != lidx) {
//                 heavyheads.push_back(c);
//                 heavy_dfs(c,i,w);
//             }
//         }
//     }

//     //finds lca of node l and r [l,r]
//     int find_lca(int l, int r) { //reverse order
//         return nodes[rmq.query(min(euler_ids[l],euler_ids[r]), max(euler_ids[l],euler_ids[r]))];
//     }

//     void update(int a, int b, T val) {
//         int lcaidx = find_lca(a,b);
//         _update(a,lcaidx,val);
//         _update(b,lcaidx,val);
//         if(nodemode) update(lcaidx,val);
//     }

//     void update(int a, T val) {
//         lazy.update(lazyidxs[a],lazyidxs[a]+1,val);
//         updateplazy(a);
//     }

//     void updateplazy(int a) {
//         plazy[heavypathidxs[a]] = lazy.query(lazyidxs[heavyheads[heavypathidxs[a]]], lazyidxs[heavytails[heavypathidxs[a]]] + 1);
//     }

//     void _update(int a, int end, T val) {
//         while(heavypathidxs[a] != heavypathidxs[end]) { //while a is not in the same path as end
//             lazy.update(lazyidxs[heavyheads[heavypathidxs[a]]], lazyidxs[a] + 1, val);
//             updateplazy(a);
//             a = parents[heavyheads[heavypathidxs[a]]];
//         }
//         lazy.update(lazyidxs[end] + 1, lazyidxs[a] + 1, val);
//         updateplazy(end);
//     }


//     T query(int a, int b) {
//         int lcaidx = find_lca(a,b);
//         // cout << "lcaidx : " << lcaidx << '\n';
//         // cout << "lhs : " << _query(a,lcaidx) << '\n';
//         // cout << "rhs : " << _query(b,lcaidx) << '\n';
//         T res = lazy.query_comb(_query(a,lcaidx),_query(b,lcaidx));
//         if(nodemode) res = lazy.query_comb(res, query(lcaidx));
//         return res;
//     }

//     T query(int a) {
//         return lazy.query(lazyidxs[a], lazyidxs[a] + 1);
//     }

//     T _query(int a, int end) {
//         T res = lazy.qn;
//         // cout << "res1 : " << res << '\n';
//         while(heavypathidxs[a] != heavypathidxs[end]) {
//             if(a == heavytails[heavypathidxs[a]]) {
//                 res = lazy.query_comb(res, plazy[heavypathidxs[a]]);
//                 assert(plazy[heavypathidxs[a]] == lazy.query(lazyidxs[heavyheads[heavypathidxs[a]]], lazyidxs[a] + 1));
//             } else {
//                 res = lazy.query_comb(res, lazy.query(lazyidxs[heavyheads[heavypathidxs[a]]], lazyidxs[a] + 1));
//             }
//             // res = lazy.query_comb(res, lazy.query(lazyidxs[heavyheads[heavypathidxs[a]]], lazyidxs[a] + 1));
//             a = parents[heavyheads[heavypathidxs[a]]];
//         }
//         // cout << "res2 : " << res << '\n';
//         res = lazy.query_comb(res, lazy.query(lazyidxs[end] + 1, lazyidxs[a] + 1));
//         // cout << "res3 : " << res << '\n';
//         return res;
//     }

//     void debugprint() {
//         cout << "parents : " << parents << endl;
//         cout << "ids : " << ids << endl;
//         cout << "nodes : " << nodes << endl;
//         cout << "euler_ids : " << euler_ids << endl;
//         cout << "euler : " << euler << endl;
//         cout << "lazyidxs : " << lazyidxs << endl;
//         cout << "heavypathidxs : " << heavypathidxs << endl;
//         cout << "subtree sizes : " << subtree_sizes << endl;
//         cout << "heavyheads : " << heavyheads << endl;
//         cout << "plazy : " << plazy << endl;
//         cout << "heavytails : " << heavytails << endl;
//     }
// };

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<vector<int>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//     }

//     HLD<int> hld(adj,a,1);
//     // hld.debugprint();

//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int s, x; cin >> s >> x;
//             s--;
//             hld.update(s,x);
//         } else {
//             int a, b; cin >> a >> b;
//             a--; b--;
//             cout << hld.query(a,b) << '\n';
//         }
//     }
//     // cout << "ENDED" << endl;
//     return 0;
// }