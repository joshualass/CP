#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n - m + 1);
    for(ll &x : a) cin >> x;
    vector<ll> deltas(n);
    for(int i = 0; i < n - m; i++) {
        deltas[i + m] = a[i+1] - a[i];
    }

    for(int i = m; i < n; i++) deltas[i] += deltas[i - m];

    // cout << deltas << '\n';

    int q; cin >> q;

    vector<array<int,2>> queries(q);
    vector<array<int,3>> mo;
    vector<ll> mo_results(q, LLONG_MAX);

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        queries[i] = {l, r};
        if(r - l >= m) mo.push_back({l, r, i});
    }

    int bs = sqrt(n);

    sort(mo.begin(), mo.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        if(lhs[0] / bs != rhs[0] / bs) return lhs[0] < rhs[0];
        if(lhs[0] / bs % 2 == 0) {
            return lhs[1] / bs < rhs[1] / bs;
        } else {
            return lhs[1] / bs > rhs[1] / bs;
        }
    });

    ll sum = 0;
    vector<multiset<ll>> s(m);

    auto add = [&](int idx) -> void {
        int group = idx % m;
        // cout << "add idx : " << idx << endl;
        // cout << "group : " << group << endl;
        if(sz(s[group])) {
            sum -= *--s[group].end();
        }
        // cout << "mih ?zz " << endl;
        s[group].insert(deltas[idx]);
        // cout << "mih ? " << endl;
        sum += *--s[group].end();
    };

    auto erase = [&](int idx) -> void {
        // cout << "erase idx : " << idx << endl;
        int group = idx % m;
        assert(sz(s[group]));
        sum -= *--s[group].end();
        s[group].erase(s[group].find(deltas[idx]));
        if(sz(s[group])) sum += *--s[group].end();
    };

    int curl = 0, curr = 0;

    for(auto [l, r, qidx] : mo) {
        // cout << "l : " << l << " r : " << r << " qidx : " << qidx << endl;
        while(curl > l) add(--curl);
        while(curr < r) add(curr++);
        while(curl < l) erase(curl++);
        while(curr > r) erase(--curr);
        mo_results[qidx] = sum;
    }

    for(int qq = 0; qq < q; qq++) {
        // cout << "qq : " << qq << endl;
        if(mo_results[qq] == LLONG_MAX) {
            cout << "unbounded\n";
        } else {
            ll val = a[0] + mo_results[qq];
            // cout << "a[0] : " << a[0] << " mo value : " << mo_results[qq] << endl;
            if(val >= 0) {
                val = (val + m - 1) / m;
            } else {
                val /= m;
            }

            cout << val << '\n';
        }
    }

    return 0;
}
