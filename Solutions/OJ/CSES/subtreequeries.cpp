#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void eulerTour(int i, int p, vector<int> &order, vector<vector<int>> &adj) {
    //version 1 - add only 2 indexes per node
    order.push_back(i);
    for(int x : adj[i]) {
        if(x != p) eulerTour(x,i,order,adj);
    }
    order.push_back(i);
    //version 2 - add a node each time for each of its children
    // order.push_back(i);
    // for(int x : adj[i]) {
    //     if(x != p) {
    //         eulerTour(x,i,order,adj);
    //         order.push_back(i);
    //     }
    // }
}

struct Tree {
    typedef ll T; //update the data type, currently int. often update to ll
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) cout << x.first << " " << x.second << "| ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> tour(0);
    eulerTour(0,-1,tour,adj);
    // cout << tour << "\n";
    unordered_map<int,pair<int,int>> m;
    int curr = 0;
    for(int i = 0; i < tour.size(); i++) {
        if(m.find(tour[i]) == m.end()) {
            m[tour[i]] = {curr++,-1};
        } else {
            m[tour[i]].second = curr;
        }
    }
    // cout << m << "\n";
    Tree tree(n);
    for(int i = 0; i < n; i++) {
        tree.update(m[i].first,v[i]);
    }
    for(int i = 0; i < q; i++) {
        int Q; cin >> Q;
        if(Q == 1) {
            int a,b;cin >> a >> b;
            a--;
            tree.update(m[a].first,b);
        } else {
            int a; cin >> a;
            a--;
            cout << tree.query(m[a].first,m[a].second) << "\n";
        }
    }

    return 0;
}