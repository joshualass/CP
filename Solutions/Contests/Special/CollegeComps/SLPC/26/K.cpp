#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

const ll inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<ll> a(n + 1);
    iota(a.begin(), a.end(), 0);

    for(ll i = 0; i < m; i++) {
        ll x, y; cin >> x >> y;
        a[y] = min(a[y], x);
    }

    ll lo = n;
    for(ll i = n; i >= 0; i--) {
        lo = min(lo, a[i]);
        a[i] = lo;
    }

    ll res = 0, cur = 0;
    //cur in stack
    vector<array<ll,2>> st; // {len, idx}

    st.push_back({inf, -1});

    ll plen = 0;

    for(ll i = 1; i <= n; i++) {
        ll len = i - a[i];

        while(plen >= len) {
            st.push_back({plen, 1});
            cur += plen;
            plen--;
        }

        ll cnt = 0;
        while(st.back()[0] <= len) {
            cur -= st.back()[0] * st.back()[1];
            cnt += st.back()[1];
            st.pop_back();
        }

        cur += cnt * len;
        st.push_back({len, cnt});

        plen = len;
        res += cur + 1LL * len * (len + 1) / 2;
    }

    cout << fixed << setprecision(15) << ((ld) res) / (1LL * n * (n + 1) / 2) << '\n';

    return 0;
}
