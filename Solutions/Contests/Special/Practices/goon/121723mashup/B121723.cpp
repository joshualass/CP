#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
template<typename T>
struct InvertedTree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    InvertedTree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void set(int pos, T val) {
        s[pos + n] = val;
    }
    void update(int l, int r, T u) { //increases values in [l,r) by u
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                s[l] = f(s[l],u);
                l++;
            }
            if(r & 1) {
                r--;
                s[r] = f(s[r],u);
            }
        }
    }
    T query(int pos) { //queries the value of element at pos
        T ans = s[pos += n];
        while(pos /= 2) {
            ans = f(ans,s[pos]);
        }
        return ans;
    }
};

void euler_tour(int i, int p, bool b, vector<int> &order, vector<int> &subtree_size, vector<int> &visitedTime, vector<vector<int>> &adj, vector<bool> &tree12) {
    visitedTime[i] = order.size();
    order.push_back(i);
    subtree_size[i] = 1;
    tree12[i] = b;
    for(int x : adj[i]) {
        if(x == p) continue;

        euler_tour(x,i, b != 1, order,subtree_size,visitedTime,adj, tree12);
        subtree_size[i] += subtree_size[x];
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);

    vector<int> starting_vals(n);
    for(auto &x : starting_vals) cin >> x;

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> order;
    vector<int> subtree_size(n);
    vector<int> visitedTime(n);
    vector<bool> tree12(n);

    euler_tour(0,-1,0,order,subtree_size,visitedTime,adj,tree12);

    InvertedTree<int> tree1(n);
    InvertedTree<int> tree2(n);

    //setup initial tree values
    for(int i = 0; i < n; i++) {
        int idx = visitedTime[i];
        if(tree12[i] == 0) {
            tree1.update(idx, idx + 1, starting_vals[i]);
        } else {
            tree2.update(idx, idx + 1, starting_vals[i]);
        }
    }

    // cout << "visitedtimes : " << visitedTime << '\n';
    // cout << "subtreesizes : " << subtree_size << '\n';
    // cout << "tree12 : " << tree12 << '\n';
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x, val; cin >> x >> val;
            x--;
            int idx = visitedTime[x];
            if(tree12[x] == 0) {
                tree1.update(idx, idx + subtree_size[x], val);
                tree2.update(idx, idx + subtree_size[x], -val);
            } else {
                tree2.update(idx, idx + subtree_size[x], val);
                tree1.update(idx, idx + subtree_size[x], -val);                
            }
        } else {
            int x; cin >> x;
            x--;
            int idx = visitedTime[x];
            if(tree12[x] == 0) {
                cout << tree1.query(idx) << '\n';
            } else {
                cout << tree2.query(idx) << '\n';
            }
        }
    }

    return 0;
}