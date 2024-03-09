#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void euler_tour(int i, int p, vector<vector<int>> &adj, vector<pair<int,int>> &euler, vector<int> &rev) {
    int idx = euler.size();
    rev[idx] = i;

    euler.push_back({idx,-1});

    for(int x : adj[i]) {
        if(x != p) {
            euler_tour(x,i,adj,euler,rev);
        }
    }
    euler[idx].second = euler.size();
}

template<typename T>
struct Tree {
    //typedef int T; //update the data type, currently int. often update to ll. Other way to do if needed
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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> colors(n);

    for(auto &x: colors) cin >> x;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n -1 ; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<pair<int,int>> euler_order;
    // vector<int> euler_index(n);
    vector<int> rev_order(n);

    euler_tour(0,-1,adj,euler_order,rev_order);

    // cout << "euler_order\n" << euler_order << '\n';
    // cout << "rev order: " << rev_order << '\n';
    map<int,priority_queue<int, vector<int>, greater<int>>> m;

    for(int i = 0; i < n; i++) {
        // int idx = euler_order[i].first;
        int idx = rev_order[i];
        m[colors[idx]].push(i);
    }

    Tree<int> tree(n);

    for(auto &x : m) {
        tree.update(x.second.top(),1);
        x.second.pop();
    }

    vector<int> ans(n);

    for(int i = 0; i < n; i++) {
        ans[rev_order[i]] = tree.query(euler_order[i].first, euler_order[i].second);
        int color = colors[rev_order[i]];
        if(m[color].size()) {
            tree.update(m[color].top(), 1);
            m[color].pop();
        }
    }

    for(auto &x : ans) cout << x << " ";
    cout << endl;

    return 0;
}