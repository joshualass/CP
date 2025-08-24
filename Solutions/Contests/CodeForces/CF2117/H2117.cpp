#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
supposedly chad (n + q) logn solution exists with O(n) memory. 


*/

void solve() {
    
    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// struct Info {
//     int lg, rg, all, res;
//     Info(): lg(0), rg(0), all(0), res(0) {}
//     Info(int n): lg(0), rg(0), all(-n), res(0) {}
//     Info(int lg, int rg, int all, int res): lg(lg), rg(rg), all(all), res(res) {}
// };

// Info operator+(Info lhs, Info rhs) {
//     Info res;
//     res.lg = max(lhs.lg, lhs.all + rhs.lg);
//     res.rg = max(rhs.rg, rhs.all + lhs.rg);
//     res.all = lhs.all + rhs.all;
//     res.res = max({lhs.res, rhs.res, lhs.rg + rhs.lg});
//     return res;
// }

// std::ostream& operator<<(std::ostream &os, const Info info) {
//     os << "(" << info.lg << ", " << info.rg << ", " << info.all << ", " << info.res << ")";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// struct Node {
//     pair<Node *, Info> left, right;
//     int l, r;
//     Info info;
//     Node(pair<Node *, Info> left, pair<Node *, Info> right, int l, int r): left(left), right(right), l(l), r(r) {
//         info = Info(r - l);
//     }
//     Node(pair<Node *, Info> left, pair<Node *, Info> right, int l, int r, Info info): left(left), right(right), l(l), r(r), info(info) {}
// };

// struct SparsestSegtree {

//     int n, nc;
//     Node *root;

//     SparsestSegtree(int n) {
//         //n = 1 is scary
//         n++;
//         this->n = n;
//         this->nc = 1;
//         int mid = n / 2;
//         root = new Node({nullptr, Info(mid)}, {nullptr, Info{n - mid}}, 0, n);
//     }

//     void update(int idx, Info info) {
//         // cout << "update called with idx : " << idx << " info : " << info << '\n';
//         // cout << "start res info : " << root->info << '\n';
//         // int mid = n / 2;
//         // auto go_left = _update(root, root->left.first, 0, mid, idx, info);
//         // auto go_right = _update(root, root->right.first, mid, n, idx, info);
//         // cout << "done left info : " << go_left.second << " right info : " << go_right.second << '\n';
//         // root->info = go_left.second + go_right.second;
//         // cout << "is root nullptr ? " << (root == nullptr) << '\n';
//         // cout << "root l : " << root->l << " root r : " << root->r << '\n';
//         // cout << "before children\n";
//         // if(root->left.first != nullptr) {
//         //     cout << "root left child info : " << root->left.first->info << '\n';
//         // } else {
//         //     cout << "root has no left child\n";
//         // }
//         // if(root->right.first != nullptr) {
//         //     cout << "root right child info : " << root->right.first->info << '\n';
//         // } else {
//         //     cout << "root has no right child\n";
//         // }
//         int curl = 0;
//         _update(root, root, curl, n, idx, info);
//         // cout << "root info : " << root->info << '\n';

//         // cout << "after children\n";
//         // if(root->left.first != nullptr) {
//         //     cout << "root left child info : " << root->left.first->info << '\n';
//         // } else {
//         //     cout << "root has no left child\n";
//         // }
//         // if(root->right.first != nullptr) {
//         //     cout << "root right child info : " << root->right.first->info << '\n';
//         // } else {
//         //     cout << "root has no right child\n";
//         // }
//     }

//     pair<Node *, Info> _update(Node *anc, Node *cur_child, int &curl, int &curr, int &idx, Info &info) {
//         // cout << "curl : " << curl << " curr : " << curr << " idx : " << idx << '\n';
//         //case stop
//         if(idx < curl || idx >= curr) {
//             // cout << "case stop\n";
//             Info res;
//             //consider this child
//             if(cur_child != nullptr && curl <= cur_child->l && cur_child->r <= curr) {
//                 // cout << " cur child info : " << cur_child->info << '\n';
//                 res = Info(cur_child->l - curl) + cur_child->info + Info(curr - cur_child->r);
//             } else {
//                 res = Info(curr - curl);
//                 cur_child = nullptr;
//             }
//             return {cur_child, res};
//         }
//         //case leaf
//         if(curl + 1 == curr) {
//             // cout << "case leaf\n";
//             // cout << "info from leaf : " << info << '\n';
//             return {new Node({nullptr, Info()}, {nullptr, Info()}, idx, idx + 1, info), info};
//         }
//         int mid = (curl + curr) / 2;
//         //case update parent node
//         if(cur_child != nullptr && cur_child->l == curl && cur_child->r == curr) {
//             // cout << "case update parent node\n";
//             anc = cur_child;
//             anc->left = _update(anc, anc->left.first, curl, mid, idx, info);
//             anc->right = _update(anc, anc->right.first, mid, curr, idx, info);
//             anc->info = anc->left.second + anc->right.second;
//             // cout << "curl : " << curl << " curr : " << curr << " idx : " << idx << " default done \n";
//             // cout << "linfo : " << anc->left.second << " rinfo : " << anc->right.second << '\n';
//             return {anc, anc->info};
//         }
//         //case create new node
//         int left_impt = idx < mid || cur_child != nullptr && cur_child->r <= mid;
//         int right_impt = idx >= mid || cur_child != nullptr && cur_child->l >= mid;
//         if(left_impt && right_impt) {
//             // cout << "case create node\n";
//             nc++;
//             Node *lca = new Node(
//                 _update(anc, cur_child, curl, mid, idx, info), 
//                 _update(anc, cur_child, mid, curr, idx, info), 
//                 curl, curr
//             );
//             lca->info = lca->left.second + lca->right.second;
//             return {lca, lca->info};
//         }
//         //default case - exactly one of the subtrees is important
//         // cout << "case default\n";
//         auto go_left = _update(anc, cur_child, curl, mid, idx, info);
//         auto go_right = _update(anc, cur_child, mid, curr, idx, info);

//         // cout << "curl : " << curl << " curr : " << curr << " idx : " << idx << '\n';
//         // cout << "linfo : " << go_left.second << " rinfo : " << go_right.second << '\n';

//         // if(go_left.first != nullptr) {
//         //     cout << "left child info : " << go_left.first->info << '\n';
//         // } else {
//         //     cout << "no left child\n";
//         // }
//         // if(go_right.first != nullptr) {
//         //     cout << "right child info : " << go_right.first->info << '\n';
//         // } else {
//         //     cout << "no right child\n";
//         // }

//         return {go_left.first != nullptr ? go_left.first : go_right.first, go_left.second + go_right.second};
//     }

//     Info query() {
//         return root->info;
//     }
// };

// void solve() {
    
//     int n, q; cin >> n >> q;
//     vector<int> a(n), b(n);
//     // vector<SparsestSegtree> trees(n, SparsestSegtree(n));
//     vector<SparsestSegtree> trees;
//     for(int i = 0; i < n; i++) trees.push_back(SparsestSegtree(n));
//     priority_queue<array<int,2>> pq;

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         // cout << "i : " << i << " x :  " << x << '\n';
//         a[i] = x;
//         trees[x].update(i, Info(1, 1, 1, 1));
//         int val = trees[x].query().res;
//         b[x] = val;
//         // cout << "i : " << i << " b[i] : " << b[i] << '\n';
//         pq.push({val, x}); 
//     }

//     // cout << "b : " << b << '\n';

//     for(int qq = 0; qq < q; qq++) {
//         int i, x; cin >> i >> x;
//         i--; x--;
//         trees[a[i]].update(i, Info(0, 0, -1, 0));
//         b[a[i]] = trees[a[i]].query().res;
//         pq.push({b[a[i]], a[i]});
//         a[i] = x;
//         trees[x].update(i, Info(1, 1, 1, 1));
//         int val = trees[x].query().res;
//         b[x] = val;
//         // cout << "i : " << i << " x : " << x << " val : " << val << '\n';
//         pq.push({val, x});
//         while(b[pq.top()[1]] != pq.top()[0]) {
//             pq.pop();
//         }
//         cout << pq.top()[0] / 2 << " \n"[qq == q - 1];
//         // cout << "pq.top x : " << pq.top()[1] << " val : " << pq.top()[0] << '\n';
//         // cout << "qq : " << qq << " b : " << b << '\n';
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// try making O(n sqrt n) runtime with O(n) memory
// none of the homies like using n logn memory XXXX

// memory forces

// */

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// const int SQN = 550;

// struct Info {
//     int res, l, r, all;
//     Info(): res(0), l(0), r(0), all(0) {}
//     Info(int res, int l, int r, int all): res(res), l(l), r(r), all(all) {}
// };

// Info operator+(Info &lhs, Info &rhs) {
//     Info res;
//     res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
//     res.l = max(lhs.l, lhs.all + rhs.l);
//     res.r = max(rhs.r, rhs.all + lhs.r);
//     res.all = lhs.all + rhs.all;
//     return res;
// }

// void solve() {
    
//     int n, q; cin >> n >> q;

//     vector<vector<array<int,2>>> bidx(n); //[value], stores {present block id, idx in bvals}
//     vector<vector<int>> bvals;
//     vector<Info> infos;

//     set<array<int,2>> vals;

//     auto get_val = [&](int val) -> array<int,2> {
//         int p = 0;
//         Info res;
//         for(int i = 0; i < (n + SQN - 1) / SQN; i++) {
//             Info nx;
//             if(p < bidx[val].size() && i == bidx[val][p][0]) {
//                 nx = infos[bidx[val][p++][1]];
//             } else {
//                 nx = Info(0, 0, 0, -SQN);
//             }
//             res = res + nx;
//         }
//         array<int,2> rv = {res.res, val};
//         // cout << "rv : " << rv << '\n';
//         return rv;
//     };

//     auto update_info = [&](int bvidx, int block_id) -> void {
//         int res = 0, l = 0, r = 0;
//         for(int i = block_id * SQN, p = 0, cur = 0, curl; i < (block_id + 1) * SQN; i++) {
//             int in = 0;
//             if(p < bvals[bvidx].size() && i == bvals[bvidx][p]) {
//                 in = 1;
//                 p++;
//             }
//             if(in) {
//                 cur++;
//                 curl++;
//             } else {
//                 cur--;
//                 curl--;
//             }
//             cur = max(cur, 0);

//             res = max(res, cur);
//             l = max(res, curl);
//         }

//         for(int i = (block_id + 1) * SQN - 1, p = bvals[bvidx].size() - 1, cur = 0; i >= block_id * SQN; i--) {
//             int in = 0;
//             if(p >= 0 && i == bvals[bvidx][p]) {
//                 in = 1;
//                 p--;
//             }
//             if(in) {
//                 cur++;
//             } else {
//                 cur--;
//             }
//             r = max(r, cur);
//         }

//         int all = -SQN * bvals[bvidx].size() * 2;
//         infos[bvidx] = Info(res, l, r, all);
//     };

//     auto insert = [&](int idx, int val) -> void {
//         // cout << "insert called idx : " << idx << " val : " << val << '\n';
//         vals.erase(get_val(val));

//         int block_id = idx / SQN;

//         int i = 0;
//         while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
//         if(!(i < bidx[val].size() && bidx[val][i][0] == block_id)) {
//             bidx[val].insert(bidx[val].begin() + i, {block_id, (int) bvals.size()});
//             bvals.push_back({});
//             infos.push_back(Info());
//         }

//         int bvidx = bidx[val][i][1];
        
//         i = 0;
//         while(i < bvals[bvidx].size() && idx > bvals[bvidx][i]) i++;
//         bvals[bvidx].insert(bvals[bvidx].begin() + i, idx);

//         update_info(bvidx, block_id);

//         vals.insert(get_val(val));
//     };

//     auto erase = [&](int idx, int val) -> void {
//         vals.erase(get_val(val));

//         int block_id = idx / SQN;

//         int i = 0;
//         while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
//         int bvidx = bidx[val][i][1];
//         int p = 0;

//         if(bvidx >= bvals.size() || count(bvals[bvidx].begin(), bvals[bvidx].end(), idx) == 0) {
//             cout << "idx : " << idx << " val : " << val << '\n';

//             cout << "i : " << i << '\n';
//             cout << "bvidx : " << bvidx << '\n';
//             for(int i = 0; i < n; i++) {
//                 cout << "i : " << i << " bidx[i] : " << bidx[i] << '\n';
//             }
//             for(int i = 0; i < bvals.size(); i++) {
//                 cout << "i : " << i << " bvals[i] : " << bvals[i] << '\n';
//             }

//             assert(0);
//         }

//         while(bvals[bvidx][p] != idx) p++;
//         bvals[bvidx].erase(bvals[bvidx].begin() + p);

//         update_info(bvidx, block_id);

//         vals.insert(get_val(val));
//     };

//     vector<int> a(n);
//     for(int i = 0; i < n; i++) {
//         cin >> a[i];
//         a[i]--;
//         insert(i, a[i]);
//     }

//     vals.insert({0, -1});

//     for(int tr = 0; tr < q; tr++) {
//         int i, x; cin >> i >> x;
//         i--, x--;
//         erase(i, a[i]);
//         a[i] = x;
//         insert(i, x);
//         cout << (*--vals.end())[0] / 2 << " \n"[tr == q - 1];
//         // cout << (*--vals.end())[0] << " \n"[tr == q - 1];
//     }


// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// int l[300000 * 18], r[300000 * 18], p[300000 * 18];
// int info[300000 * 18][4];
// int a[300000];


// void solve() {
    
    

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// have some data structure that can support the following operation
// for a given index i, find the largest k-majority possible that includes this element 
// */

// struct Info {
//     int res, l, r, all;
//     Info(): res(0), l(0), r(0), all(0) {}
//     Info(int res, int l, int r, int all): res(res), l(l), r(r), all(all) {}
// };

// Info operator+(Info lhs, Info rhs) {
//     Info res;
//     res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
//     res.l = max(lhs.l, lhs.all + rhs.l);
//     res.r = max(rhs.r, rhs.all + lhs.r);
//     res.all = lhs.all + rhs.all;
//     return res;
// }

// Info base;
// struct Tree {
//     typedef Info T;
//     vector<unordered_map<int, Info>> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     T get(int x, int cur) {
//         if(v[cur].count(x)) {
//             return v[cur][x];
//         }
//         int depth = 31 - __builtin_clz(cur);
//         int sz = size >> depth;
//         return Info(0, 0, 0, -sz);
//     }
//     void upd(int x, int cur, T info) {
//         int depth = 31 - __builtin_clz(cur);
//         int sz = size >> depth;
//         if(info.l == 0 && info.r == 0 && info.res == 0 && info.all == -sz) {
//             v[cur].erase(x);
//         } else {
//             v[cur][x] = info;
//         }
//     }
//     Tree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.resize(size * 2);
//     }
//     void update(int pos, int x, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         upd(x, curr, val);
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 upd(x, curr / 2, f(get(x, curr ^ 1), get(x, curr)));
//             } else {
//                 upd(x, curr / 2, f(get(x, curr), get(x, curr ^ 1)));
//             }
//             curr /= 2;
//         }
//     }
//     T query(int x) {
//         return get(x, 1);
//     }
// };

// void solve() {
    
//     int n, q; cin >> n >> q;
//     vector<int> a(n);
//     Tree tree(n);

//     priority_queue<array<int,2>> pq;

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         a[i] = x;
//         tree.update(i, x, Info(1, 1, 1, 1));
//         pq.push({tree.query(x).res, x});
//     }

//     for(int i = 0; i < q; i++) {
//         int idx, x; cin >> idx >> x;
//         idx--;
        
//         tree.update(idx, a[idx], Info(0, 0, 0, -1));
//         pq.push({tree.query(a[idx]).res, a[idx]});

//         a[idx] = x;
//         tree.update(idx, x, Info(1,1,1,1));
//         pq.push({tree.query(x).res, x});

//         while(1) {
//             auto [val, x] = pq.top();
//             if(val == tree.query(x).res) break;
//             pq.pop();
//         }
//         cout << pq.top()[0] / 2 << " \n"[i == q - 1];
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }