// does not work. need hld. going to write lazy segtree and then hld
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// //range minimum query. O(1) query, O(n) build/memory. fast.
// template<typename T>
// struct RMQ  {
//     vector<T> elements;
//     int n;
//     static const int block_size = 30; // block size. adjust accordingly
//     vector<int> mask;
//     vector<int> sparse_table;

//     //type of function the table is storing. Currently, it stores the minimum because it returns the minimum index 
//     int op(int x, int y) { 
//         return elements[x] < elements[y] ? x : y;
//     }

//     int least_significant_bit(int x) {
//         return x & -x;
//     }
    
//     int most_significant_bit_index(int x) {
//         return 31 - __builtin_clz(x);
//     }

//     // answers the smaller queries given size is <= b. elements[r-size+1..r] using masks
//     int small_query(int r, int size = block_size) {
//         //get only the 'size' least significant bits from the mask
//         //with that, get the most significant set bit
//         int dist_from_r = most_significant_bit_index(mask[r] & ((1<<size)-1));
//         return r - dist_from_r;
//     }

//     RMQ() {} //need this to satisfy master goon's requirements

//     //constructor
//     RMQ (const vector<T>& input): elements(input), n(input.size()), mask(n), sparse_table(n) {
//         //construct masks for all elements
//         int curr_mask = 0;
//         for(int i = 0; i < n; i++) {
//             //shift mask by 1, keeping only the 'b' least significant bits
//             curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
//             //while the current value is smaller than the value least significant bit of curr_mask
//             //update that 0 into a 1. 
//             while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
//                 curr_mask ^= least_significant_bit(curr_mask);
//             }
//             //the least bit will always be minimum in that small bit
//             curr_mask |= 1;
//             mask[i] = curr_mask;
//         }
//         //construct sparse table for the n / b blocks
//         //lower level
//         for(int i = 0; i < n/block_size; i++) {
//             sparse_table[i] = small_query(block_size * i + block_size - 1);
//         }
//         //rest of the levels
//         for(int j = 1; (1<<j) <= n/block_size; j++) {
//             for(int i = 0; i + (1<<j) <= n / block_size; i++) {
//                 sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
//             }
//         }

//     }

//     //query(l,r) returns the element from the minimum of v[l..r]
//     //can be updated to return index by changing what we are returning
//     T query(int l, int r) {
//         //query size <= b
//         if(r - l + 1 <= block_size) {
//             return elements[small_query(r, r - l + 1)];
//             // return small_query(r, r- l + 1);
//         }

//         //work out the small parts of the answer
//         //it's ok for it to overlap and because size > b, we can freely let size of both sides be b
//         int ans = op(small_query(l + block_size - 1), small_query(r)); 

//         //blocks to query over
//         int x = l / block_size + 1;
//         int y = r / block_size - 1;

//         if(x <= y) {
//             int j = most_significant_bit_index(y - x + 1);
//             ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
//         }

//         return elements[ans];
//         // return ans;
//     }

//     //alternative way to build if can't easily do with constructor or want to reuse
//     void build (const vector<T>& input) {
//         elements = input;
//         n = input.size();
//         mask.assign(n,0);
//         sparse_table.assign(n,0);
        
//         //construct masks for all elements
//         int curr_mask = 0;
//         for(int i = 0; i < n; i++) {
//             //shift mask by 1, keeping only the 'b' least significant bits
//             curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
//             //while the current value is smaller than the value least significant bit of curr_mask
//             //update that 0 into a 1. 
//             while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
//                 curr_mask ^= least_significant_bit(curr_mask);
//             }
//             //the least bit will always be minimum in that small bit
//             curr_mask |= 1;
//             mask[i] = curr_mask;
//         }
//         //construct sparse table for the n / b blocks
//         //lower level
//         for(int i = 0; i < n/block_size; i++) {
//             sparse_table[i] = small_query(block_size * i + block_size - 1);
//         }
//         //rest of the levels
//         for(int j = 1; (1<<j) <= n/block_size; j++) {
//             for(int i = 0; i + (1<<j) <= n / block_size; i++) {
//                 sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
//             }
//         }

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
//         this->n = parents.size();
//         adj.assign(n, {});
//         for(int i = 1; i < n; i++) {
//             adj[i].push_back(parents[i]);
//             adj[parents[i]].push_back(i);
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

//     //assigns id in a level traversal manner so rmq works
//     void assign_ids() {
//         queue<pair<int,int>> q; //curr, parent
//         int id = 0;
//         q.push({0,-1});
//         while(q.size()) {
//             pair<int,int> p = q.front();
//             q.pop();
//             ids[p.first] = id;
//             nodes[id++] = p.first;
//             for(auto x : adj[p.first]) {
//                 if(x != p.second) {
//                     q.push({x,p.first});
//                 }
//             }   
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

// void dfs(int i, int p, int curr, vector<vector<int>> &adj, vector<pair<int,int>> &cnts, vector<int> &ans) {
//     cout << "i : " << i << " curr before : " << curr << '\n';
//     curr += cnts[i].first;
//     ans[i] = curr;
//     curr -= cnts[i].second;
//     cout << "i : " << i << " curr after : " << curr << '\n';
//     for(int child : adj[i]) {
//         if(child != p) {
//             dfs(child, i, curr, adj, cnts, ans);
//         }
//     }
// }

// template <typename T, typename D>
// std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
//     os << '(' << p.first << ", " << p.second << ") ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto &x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     vector<vector<int>> adj(n);

//     for(int i = 0; i < n - 1; i++) { //for trees
//     // for(int i = 0; i < m; i++) { //for graphs with m edges
//         int a, b; cin >> a >> b;
//         a--; b--; //1 -> 0 indexed
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//     }

//     LCA tree(adj);

//     vector<pair<int,int>> cnts(n);

//     for(int i = 0; i < m; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         int lca = tree.find_lca(a,b);
//         cout << "a : " << a << " b : " << b << " lca : " << lca << '\n';
//         cnts[lca].first++;
//         if(a != lca) {
//             cnts[a].second++;
//         }
//         if(b != lca) {
//             cnts[b].second++;
//         }
//     }

//     vector<int> ans(n);
//     cout << "cnts : " << cnts << '\n';
//     dfs(0,-1,0,adj,cnts,ans);

//     for(int i = 0; i < n; i++) {
//         cout << ans[i] << " \n"[i == n - 1];
//     }

//     return 0;
// }