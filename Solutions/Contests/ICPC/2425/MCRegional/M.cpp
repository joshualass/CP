#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
tc
4 0
1 0
4 3
7 6
10 9

4 10
9 10
6 7
3 4
0 1
*/

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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll solve(vector<array<ll,2>> h, ll h0) {

    ll lostart = LLONG_MAX;
    ll maxup = h0;

    // cout << "h : " << h << '\n';

    map<ll,ll> ups;

    for(auto [u, v] : h) {
        if(v > u) {
            if(ups.count(u) == 0) {
                ups[u] = v;
            } else {
                ll val = max(ups[u],v);
                ups[u] = val;
            }
            lostart = min(lostart, u);
            maxup = max(maxup, v);
        } else {
            lostart = min(lostart, v);
            maxup = max(maxup, u);
        }
    }

    ll prevmincost = 1e18;
    ll maxheightvis = lostart;
    ll prevlo = lostart;

    // cout << "ups : " << ups << '\n';
    // cout << "maxup : " << maxup << " lo start : " << lostart << " maxheightvis : " << maxheightvis << " prevlo : " << prevlo << '\n';

    map<ll,ll> dp;

    for(map<ll,ll>::iterator it = ups.begin(); it != ups.end(); it++) {
        auto [start, end] = *it;
        // cout << "start : " << start << " end : " << end << '\n';
        ll mincostgodown  = min(max(0LL, 2 * (end - maxheightvis)) + prevmincost + start - prevlo, (end - start) * 2 + min(start - lostart + maxheightvis - lostart, prevmincost + start - prevlo));
        prevmincost = mincostgodown;
        maxheightvis = max(maxheightvis, end);
        prevlo = start;
        dp[start] = min(mincostgodown, maxheightvis + start - lostart * 2);
    }

    // cout << "dp : " << dp << '\n';

    auto getabove_cost = [&](ll sh) -> ll {
        if(dp.lower_bound(sh) == dp.begin()) {
            return sh - lostart;
        }
        auto [startup, cost] = *--dp.lower_bound(sh);
        return sh - startup + cost;
    };


    auto getcost = [&](ll startup) -> ll {
        ll cost = maxup * 2 + h0 - startup * 3 + getabove_cost(startup);
        // cout << "startup : " << startup << " cost : " << cost << " get below costs : " << maxup * 2 + h0 - startup * 3 << " getabove costs : " << getabove_cost(startup) << '\n';
        return cost;
    };

    ll res = getcost(h0);
    for(auto [startup, cost] : dp) {
        if(startup < h0) {
            res = min(res, getcost(startup));
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, h0; cin >> n >> h0;
    vector<array<ll,2>> h(n);
    for(auto &x : h) {
        cin >> x[0] >> x[1];
    }

    ll t = solve(h,h0);
    h0 *= -1;
    for(auto &x : h) {
        x[0] *= -1;
        x[1] *= -1;
    }
    cout << min(t, solve(h,h0)) << '\n';

    return 0;
}