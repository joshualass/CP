#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
struct InvertedTree {
    typedef ll T; //update the data type, currently int. often update to ll
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

void eulerTour(int i, int p, vector<int> &order, vector<vector<int>> &adj) {
    //version 1 - add only 2 indexes per node
    order.push_back(i);
    for(int x : adj[i]) {
        if(x != p) eulerTour(x,i,order,adj);
    }
    order.push_back(i);
}

const ll N = 5e5;

int parents[N + 1];

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}


void solve() {
    
    int q; cin >> q;

    vector<vector<ll>> queries(q);
    vector<vector<int>> adj(1);
    parents[0] = -1;

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int parent; cin >> parent;
            parent--;
            int child = adj.size();
            adj.push_back({});
            adj[parent].push_back(child);
            adj[child].push_back(parent);
            queries[i] = {type, child};
            parents[child] = parent;
        } else if(type == 2) {
            ll x, v; cin >> v >> x;
            queries[i] = {type, v, x};
        }
    }

    vector<int> tour(0);
    eulerTour(0, -1, tour, adj);

    map<ll,pair<ll,ll>> m;
    int curr = 0;
    for(int i = 0; i < tour.size(); i++) {
        if(m.find(tour[i]) == m.end()) {
            m[tour[i]] = {curr++, -1};
        } else {
            m[tour[i]].second = curr;
        }
    }

    // cout << "m\n" << m << '\n';

    InvertedTree tree(adj.size());

    for(int i = 0; i < q; i++) {
        if(queries[i][0] == 1) { //add element
            //subtract current parent sum
            // subs[queries[i][1]] = tree.query(parents[queries[i][1]]);
            // ll node = queries[i][1];
            // ll idx = m[node].first;

            // tree.update(idx, idx + 1 , 0);

            //reset all subtrees to 0

            ll node = queries[i][1];
            ll idx = m[node].first;

            ll currval = tree.query(idx);

            tree.update(m[node].first, m[node].second, -currval);

        } else {
            ll x = queries[i][2];
            ll node = queries[i][1];
            node--;
            ll lo = m[node].first;
            ll hi = m[node].second;
            tree.update(lo, hi, x);
        }
    }

    for(int i = 0; i < adj.size(); i++) {
        cout << tree.query(m[i].first) << " ";
    }
    cout << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}