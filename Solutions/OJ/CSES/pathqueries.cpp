#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void euler_tour(int i, int p, vector<int> &order, vector<int> &subtree_size, vector<int> &visitedTime, vector<vector<int>> &adj) {
    visitedTime[i] = order.size();
    order.push_back(i);
    subtree_size[i] = 1;

    for(int x : adj[i]) {
        if(x == p) continue;

        euler_tour(x,i,order,subtree_size,visitedTime,adj);
        subtree_size[i] += subtree_size[x];
    }

}

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
// could be modified to handle assignment, but just use lazy seg at that point
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<ll> values(n);

    for(auto &x: values) cin >> x;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> euler_order; //for index i in the euler order, stores which input index it's associated with
    vector<int> subtree_size(n); //for index i, stores in the input order, stores size
    vector<int> inTime(n); //for index i, stores the index it appears in the euler tour

    euler_tour(0,-1,euler_order,subtree_size,inTime,adj);

    // cout << "order: " << euler_order << '\n';
    // cout << "sizes: " << subtree_size << '\n';
    // cout << "intime: " << inTime << '\n';


    InvertedTree<ll> tree(n);

    for(int i = 0; i < n; i++) {
        int i_size = subtree_size[i];
        int idx = inTime[i];
        tree.update(idx, idx + i_size, values[i]);
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll s, x; cin >> s >> x;
            s--;
            tree.update(inTime[s], inTime[s] + subtree_size[s], x - values[s]);
            values[s] = x;
        } else {
            int s; cin >> s;
            s--;
            cout << tree.query(inTime[s]) << '\n';
        }
    }

    return 0;
}