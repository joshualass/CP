#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

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

void solve() {
    
    ll n, q; cin >> n >> q;
    vector<vector<ll>> ch(n + 1);
    for(ll i = 1; i <= n; i++) {
        ll l, r; cin >> l >> r;
        if(l) {
            ch[i].push_back(l);
            ch[i].push_back(r);
        }
    }

    vector<ll> tour_order;
    vector<ll> tour_idx(n + 1);
    vector<ll> ss(n + 1);

    auto dfs = [&](auto self, ll i) -> ll {
        ll sz = 1;
        tour_idx[i] = tour_order.size();
        tour_order.push_back(i);
        for(ll c : ch[i]) { 
            sz += self(self, c);
            tour_order.push_back(i);
        }
        ss[i] = sz;
        return sz;
    };

    dfs(dfs, 1);

    // cout << "tour_order : " << tour_order << '\n';
    // cout << "tour_idx : " << tour_idx << '\n';
    // cout << "ss : " << ss << '\n';

    vector<vector<array<ll,2>>> queries(n + 1);
    for(ll qq = 0; qq < q; qq++) {
        ll v, k; cin >> v >> k;
        queries[v].push_back({k, qq});
    }

    vector<ll> res(q);
    vector<array<ll,2>> st;

    auto dfs2 = [&](auto self, ll i) -> void {
        st.push_back({(i == 1 ? 0 : st.back()[0]) + ss[i] * 2 - 1, i});
        for(auto [k, q_idx] : queries[i]) {
            // cout << "i : " << i << " k : " << k << '\n';
            // cout << "st : " << st << '\n';
            ll rk = st.back()[0] - k - 1;
            auto it = upper_bound(st.begin(), st.end(), array<ll,2>{rk, LLONG_MAX});
            k -= st.back()[0] - (*it)[0];
            ll v = (*it)[1];
            // cout << "k : " << k << " v : " << '\n';
            res[q_idx] = tour_order[tour_idx[v] + k];
        }
        for(ll c : ch[i]) self(self, c);
        st.pop_back();
    };

    dfs2(dfs2, 1);
    for(ll i = 0; i < q; i++) cout << res[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}