#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<set<array<ll,2>>> b(2);
    vector<int> bid(n);
    vector<ll> s(n);
    ll sum = 0;

    int cnt = 0;

    for(int i = 0; i < n; i++) {
        if(sz(adj[i]) == 1) {
            if(cnt + 1 <= k - 1) {
                b[0].insert({0, i});
                bid[i] = 0;
            } else {
                b[1].insert({0, i});
                bid[i] = 1;
            }
            cnt++;
        }
    }

    auto upd_size = [&](int idx, ll delta) -> void {

        // cout << "us idx : " << idx << " del : " << delta << endl;
        // cout << "b : " << b << endl;
        // cout << "bid : " << bid << endl;
        // cout << "s : " << s << endl;

        if(bid[idx] == 0) sum -= s[idx];

        assert(b[bid[idx]].count({s[idx], idx}));
        b[bid[idx]].erase({s[idx], idx});

        s[idx] += delta;
        if(b[1].empty() || s[idx] >= (*--b[1].end())[0]) {
            b[0].insert({s[idx], idx});
            bid[idx] = 0;
            sum += s[idx];
        } else {
            b[1].insert({s[idx], idx});
            bid[idx] = 1;
        }

        while(sz(b[0]) < k - 1 && sz(b[1])) {
            auto last = *--b[1].end();
            b[1].erase(last);
            b[0].insert(last);
            sum += last[0];
            bid[last[1]] = 0;
        }
        while(sz(b[0]) > k - 1) {
            auto last = *b[0].begin();
            b[0].erase(last);
            b[1].insert(last);
            sum -= last[0];
            bid[last[1]] = 1;
        }
    };

    vector<array<int,2>> bests(n);

    auto dfs_start = [&](auto self, int i, int p, int d) -> void {
        // cout << "i : " << i << " p : " << p << " d : " << d << endl;
        bests[i] = {n - d, i};
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, d + 1);
                bests[i] = min(bests[i], bests[c]);
            }
        }
        if(i) {
            upd_size(bests[i][1], a[i]);
        }
    };

    dfs_start(dfs_start, 0, -1, 0);

    ll res = 0;

    // cout << "adj" << endl;
    // for(int i = 0; i < n; i++) cout << "i : " << i << " adj[i] : " << adj[i] << endl;

    auto dfs = [&](auto self, int i, int p, array<int,2> par_best) -> void {

        // cout << "i : " << i << " p : " << p << " pb : " << par_best << endl;

        //assume that index i is ready to query
        res = max(res, sum + a[i]);

        vector<int> ch;
        for(int c : adj[i]) {
            if(c != p) ch.push_back(c);
        }
        vector<array<int,2>> pre, suf;
        pre.push_back(par_best);
        suf.push_back(par_best);
        for(int i = 0; i < sz(ch); i++) {
            pre.push_back(min(pre.back(), bests[ch[i]]));
            suf.push_back(min(suf.back(), bests[ch[sz(ch) - 1 - i]]));
        }

        reverse(suf.begin(), suf.end());
        
        // cout << "ch : " << ch << endl;
        // cout << "pre : " << pre << endl;
        // cout << "suf : " << suf << endl;

        for(int j = 0; j < sz(ch); j++) {
            int c = ch[j];
            auto best = min(pre[j], suf[j+1]);
            upd_size(best[1], a[i]);
            upd_size(bests[c][1], -a[c]);

            self(self, c, i, {best[0] - 2, best[1]});

            upd_size(best[1], -a[i]);
            upd_size(bests[c][1], a[c]);
        }
    };

    dfs(dfs, 0, -1, {n, 0}); 

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}