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

/*
thought about this problem for a couple of hours already and no dice. I peeked at editorial and saw they were able to get a time complexity of O((n + q) logn), so 
I won't try to squeeze any log^2n approaches. 

There are two main approaches that I could think of
The first, is some sort of euler tour on the tree, maintaining a lazy segment tree, where each element in the lazy segment tree 
stores some query time. The current problem with this type of approach is that when we go down some branch, we have to undo the other branches' queries 
that are no longer relevant. With this approach, we might include/exclude updates a lot of times. 

Another way to try doing this dfs is with a tree-dp like approach, where each node returns the set of intervals when it is bad and somehow propagate to the 
parent and do this with some small to large merging, but not sure how to do this either. 

A third approach that I've considered is an online type of approach, where we maintain for each node, how many operations away it is from being good, but we need to be able 
to toggle both paths to root and subtract / add to subtrees. 

Regardless of how we solve this problem, it is helpful to use the observation that we really only care about whether a child differs from its parent + when a node is black. 
Also, when we add to our counts, we need that all the children differ, and beyond that, everything is the same, which doesn't happen often. 

After writing this up, I realize the dfs strat won't work because we need to sum for each query, not the total or whatever ... so we should consider something like the 
online approach. 

Also, when some node contributes, none of its children can contribute, but this is quite obvious. how can we use this to help?
It seems like there is some amortized trick we can use to analyze the candidates for this black node ... 

maintain a set of candidates
create an HLD-like data structure to store the earliest occurrence of element in our candidate set. 

there are very few limited / ready to go candidates in a path ... then use candidate approach, but this is quite sloppy, but still works. 
*/

//data structure to find nearest candidate parent and stuff. 

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

int debug = 0;

struct DS {
    int n;
    vector<vector<int>> adj;
    vector<int> ss, time, rtime, par, seg_id;

    struct seg {
        int leader = -1; //leader is in normal form. 
        set<int> s;
        int mx = 1e9;
        seg() {}
        seg(int leader): leader(leader) {}
        void upd_mx() {
            if(s.empty()) {
                mx = 1e9;
            } else {
                mx = *s.begin();
            }
        }
        void add(int x) {
            s.insert(x);
            upd_mx();
        }
        void erase(int x) {
            s.erase(x);
            upd_mx();
        }
        //query for the highest value <= t 
        int query(int t) {
            if(mx <= t) {
                return *--s.upper_bound(t);
            } else {
                return 1e9;
            }
        }
    };

    vector<seg> segs;

    DS(vector<vector<int>> adj) {
        this->adj = adj;
        build();
        if(debug) {
            cout << "ss : " << ss << "\n";
            cout << "time : " << time << '\n';
            cout << "rtime : " << rtime << '\n';
            cout << "par : " << par << '\n';
            cout << "segs size : " << segs.size() << '\n';
            cout << "seg_id : " << seg_id << '\n';
        }
    }

    void build() {
        this->n = adj.size();
        ss.assign(n, -1);
        time.assign(n, -1);
        rtime.assign(n, -1);
        par.assign(n, -1);

        int curr_time = 0;
        
        //compute ss, par, time, 
        auto dfs = [&](auto self, int i, int p) -> int {
            time[i] = curr_time;
            rtime[curr_time++] = i;
            par[i] = p;
            int sz = 1;

            for(int c : adj[i]) {
                if(c != p) {
                    sz += self(self, c, i);
                }
            }

            ss[i] = sz;
            return sz;
        };

        dfs(dfs, 0, -1);

        seg_id.assign(n, -1);

        auto dfs_seg = [&](auto self, int i, int p, int curr_seg_id) -> void {
            seg_id[i] = curr_seg_id;
            int hc = -1, hw = 0;
            for(int c : adj[i]) {
                if(c != p) {
                    if(ss[c] > hw) {
                        hc = c;
                        hw = ss[c];
                    }
                }
            }
            
            if(hc == -1) return;

            for(int c : adj[i]) {
                if(c != p) {
                    if(c == hc) {
                        self(self, c, i, curr_seg_id);
                    } else {
                        int nx_id = segs.size();
                        segs.push_back(seg(c));
                        self(self, c, i, nx_id);
                    }
                }
            }
        };

        segs.push_back(seg(0));
        dfs_seg(dfs_seg, 0, -1, 0);
    }

    void insert(int x) {
        int id = seg_id[x];
        segs[id].add(time[x]);
    }

    void erase(int x) {
        int id = seg_id[x];
        segs[id].erase(time[x]);
    }

    int query(int x) {
        while(x != -1) {
            int id = seg_id[x];
            int res = segs[id].query(time[x]);
            if(res == 1e9) {
                int leader = segs[id].leader;
                x = par[leader];
            } else {
                return rtime[res];
            }
        }
        return -1;
    }
};

// T - query val, D - lazy change
struct Lazy {
    typedef array<array<int,2>,2> T;
    typedef array<int,2> D;
    static constexpr T qn = {}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {}; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(vector<T>(n, def));
    }
    Lazy(int n, vector<T> a) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(a);
    }   
    void build(vector<T> a) {
        for(int i = 0; i < a.size(); i++) v[i + size] = a[i];
        for(int i = size - 1; i >= 1; i--) {
            v[i] = query_comb(v[i * 2], v[i * 2 + 1]);
        }
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        T res = {};
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                res[i][j] = val1[i][j] + val2[i][j];
            }
        }
        return res;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        for(int i = 0; i < 2; i++) {
            lazy[node][i] ^= val[i];
        }
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        if(lazy[node][0]) {
            swap(v[node][0][0], v[node][1][0]);
            swap(v[node][0][1], v[node][1][1]);
        }
        if(lazy[node][1]) {
            swap(v[node][0][0], v[node][0][1]);
            swap(v[node][1][0], v[node][1][1]);
        }
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, D val) { //[l,r)
        if(debug) {
            cout << "update called l : " << l << " r : " << r << " val : " << val << '\n';
        }
        _update(1,0,size,l,r, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            int mid = (currl + currr) / 2;
            return query_comb(
                _query(node * 2, currl, mid, targetl, targetr),
                _query(node * 2 + 1, mid, currr, targetl, targetr)
            );
        }
    }
};

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def = base) {
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
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
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
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

void solve() {
    
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

    vector<int> tin(n), tout(n), par(n);
    vector<array<int,2>> ch_cnt(n);
    vector<int> leafs;
    int time = 0;
    auto dfs = [&](auto self, int i, int p) -> void {
        tin[i] = time++;
        par[i] = p;
        for(int c : adj[i]) {
            if(c != p) {
                ch_cnt[i][0]++;
                self(self, c, i);
            }
        }
        if(ch_cnt[i][0] == 0) {
            leafs.push_back(i);
        }
        tout[i] = time;
    };

    dfs(dfs, 0, -1);

    if(debug) {
        cout << "tin : " << tin << '\n';
        cout << "tout : " << tout << '\n';
        cout << "par : " << par << '\n';
        cout << "leafs : " << leafs << '\n';
    }

    array<array<int,2>,2> start = array<array<int,2>,2>{array<int,2>{1,0},array<int,2>{0,0}};
    Lazy lazy(n, vector<array<array<int,2>,2>>(n, start));

    Tree<int> tree(n);
    DS ds(adj);
    vector<int> current_states(n);
    vector<int> on(n);

    auto add = [&](int idx) -> void {
        int type = current_states[idx];
        if(type == 1) {
            tree.update(tin[idx], 1);
            ds.insert(idx);
        } else if(type == 2) {
            lazy.update(tin[idx], tin[idx] + 1, {0, 1});
            tree.update(tin[idx], 1);
            ds.insert(idx);
        }
    };

    auto remove = [&](int idx) -> void {
        int type = current_states[idx];
        if(type == 1) {
            tree.update(tin[idx], 0);
            ds.erase(idx);
        } else if(type == 2) {
            lazy.update(tin[idx], tin[idx] + 1, {0, 1});
            tree.update(tin[idx], 0);
            ds.erase(idx);
        }
    };

    auto update_state = [&](int idx) -> void {
        if(debug) {
            cout << "update state idx : " << idx << '\n';
        }
        remove(idx);
        //figure which type it is
        if(ch_cnt[idx][1]) { 
            if(ch_cnt[idx][0] == ch_cnt[idx][1] && (tree.query(tin[idx], tout[idx]) - tree.query(tin[idx], tin[idx] + 1)) == 0) {
                current_states[idx] = 2;
            } else {
                current_states[idx] = 1;
            }
        } else {
            current_states[idx] = 0;
        }
        add(idx);
    };

    for(int l : leafs) {
        current_states[l] = 2;    
        lazy.update(tin[l], tin[l] + 1, {0, 1});
    }

    auto op = [&](int idx) -> void {
        //toggle all values in subtree
        if(debug) {
            cout << "op - idx : " << idx << '\n';
        }
        lazy.update(tin[idx], tout[idx], {1, 0});

        if(idx) {
            int p = par[idx];
            if(on[idx]) {
                ch_cnt[p][1]--;
            } else {
                ch_cnt[p][1]++;
            }
            on[idx] ^= 1;
            update_state(p);
            if(p) {
                int pp = ds.query(par[p]);
                if(pp != -1) {
                    update_state(pp);
                }
            }
        }
    };

    auto query = [&]() -> int {
        return lazy.query(0, n)[1][1];
    };

    auto dfs_start = [&](auto self, int i, int p) -> void {
        auto val = lazy.query(tin[i], tin[i] + 1);
        int cur = val[1][0] + val[1][1];
        if(cur != a[i]) op(i);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
    };

    dfs_start(dfs_start, 0, -1);

    auto print_state = [&]() -> void {
        cout << "states : " << current_states << '\n';
        cout << "colors :";
        for(int i = 0; i < n; i++) {
            int c = 0;
            auto val = lazy.query(tin[i], tin[i] + 1);
            // cout << "i : " << i << " val : " << val << '\n';
            for(int j = 0; j < 2; j++) {
                c += val[1][j];
            }
            cout << " " << c;
        }
        cout << '\n';
        cout << "ch_cnts : " << ch_cnt << '\n';
    };
    if(debug) {
        cout << "starting states\n";
        print_state();
    }

    cout << query() << '\n';
    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int x; cin >> x;
        x--;
        op(x);
        cout << query() << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}