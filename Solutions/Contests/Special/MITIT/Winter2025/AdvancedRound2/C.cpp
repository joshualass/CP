#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e18;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = inf; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    ll n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(ll n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(ll node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return min(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(ll node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(ll node, ll size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node];
    }
    void push_lazy(ll node, ll size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(ll l, ll r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(ll node, ll currl, ll currr, ll &targetl, ll &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            ll mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(ll l, ll r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(ll node, ll currl, ll currr, ll &targetl, ll &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            ll mid = (currl + currr) / 2;
            return query_comb(
                _query(node * 2, currl, mid, targetl, targetr),
                _query(node * 2 + 1, mid, currr, targetl, targetr)
            );
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<vector<array<ll,3>>> atdepths(n); //atdepth[i] stores the set of nodes which are at depth i, stores {node, parent_idx, edge weight to parent}
    vector<vector<array<ll,2>>> sadj(n); //starting adjacency list 
    vector<unordered_map<ll,ll>> cadj(n); //compressed adj list
    vector<ll> dists(n); //dists from root
    vector<ll> depths(n); //depths in tree
    ll maxdepth = 0;

    for(ll i = 1; i < n; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        sadj[u].push_back({v,w});
        sadj[v].push_back({u,w});
    }

    auto dfs0 = [&](auto self, ll i, ll p, ll depth, ll dist) -> void {
        depths[i] = depth;
        dists[i] = dist;
        maxdepth = max(maxdepth, depth);
        for(auto [c, w] : sadj[i]) {
            if(c == p) {
                atdepths[depth].push_back({i, p, w});
            } else {
                self(self, c, i, depth + 1, dist + w);
            }
        }
    };

    //initialize atdepths, dists, depths, and maxdepth. 
    dfs0(dfs0, 0, -1, 0, 0);
    vector<ll> dp(n);

    auto compute_depth = [&](ll depth) {
        if(depth > 1) {
            map<ll,array<ll,2>> m;
            auto euler = [&](auto self, ll i) -> void {
                ll sz = m.size();
                m[i][0] = sz;
                for(auto [c, w] : cadj[i]) {
                    self(self, c);
                }
                m[i][1] = m.size();
            };


            euler(euler, 0);
            ll gs = m.size();

            Lazy<ll,ll> lazy(gs);
            for(auto [i, t] : m) {
                if(depths[i] == depth - 1) {
                    lazy.update(t[0], t[1], dp[i] + dists[i] - inf);
                }
            }   

            auto lazydfs = [&](auto self, ll i) -> void {
                for(auto [c, w] : cadj[i]) {
                    lazy.update(m[c][0], m[c][1], -w * 2);
                    self(self, c);
                    lazy.update(m[c][0], m[c][1], w * 2);
                }
                if(depths[i] == depth - 1) {
                    dp[i] = dists[i] + min(lazy.query(0, m[i][0]), lazy.query(m[i][1], gs));
                }
            };

            lazydfs(lazydfs, 0);
        }

        for(auto [i, p, w]: atdepths[depth]) {
            dp[i] = dp[p] + w;
            cadj[p][i] = w;
        }

        auto compressdfs = [&](auto self, ll i) -> array<ll,2> {
            if(depths[i] == depth) {
                return {i,0};
            }
            vector<array<ll,2>> t;
            for(auto [c, w] : cadj[i]) {
                array<ll,2> a = self(self, c);
                a[1] += w;
                if(a[0]) t.push_back(a);
            }
            cadj[i].clear();
            if(t.size() >= 2 || i == 0) {
                for(auto [c, w] : t) {
                    cadj[i][c] = w;
                }
                return {i, 0};
            } else if(t.size() == 1) {
                return t[0];
            } else {
                return {0,0};
            }
        };

        compressdfs(compressdfs, 0);

    };

    for(ll d = 1; d <= maxdepth; d++) {
        compute_depth(d);
    }

    ll res = inf;
    for(ll i = 0; i < n; i++) {
        if(depths[i] == maxdepth) res = min(res, dp[i]);
    }

    cout << res << '\n';

    return 0;
}