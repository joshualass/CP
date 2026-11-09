#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    int cnt = 0;
    ll cb = 0;
    vector<int> p(n + 1);
    vector<ll> a(n + 1);

    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] + (s[i] == '1');
        a[i+1] = a[i] + (s[i] == '1') * i;
    }

    // cout << "a : " << a << endl;
    // cout << "p : " << p << endl;

    auto getc = [&](int len) -> array<ll,3> {
        // cout << "len : " << len << endl;
        ll left, right, start;
        ll mid = len / 2;
        if(len % 2 == 0) {
            left = p[mid] * mid - a[mid];
            right = a[n] - a[mid] - (p[n] - p[mid]) * (mid - 1);
            start = n - mid + 1;
        } else {
            left = p[mid] * mid - a[mid];
            right = (a[n] - a[mid]) - (p[n] - p[mid]) * mid;
            start = n - mid;
        }
        ll max_cnt = len - n;
        // cout << "left : " << left << " right : " << right << " mid : " << mid << endl;
        return {left - right, start, max_cnt};
    };

    auto get_range = [&](ll cnt, ll start, ll max_cnt) -> array<ll,2> {
        ll lo = start * cnt + cnt * (cnt - 1) / 2;
        ll hi = (start + (max_cnt - cnt)) * cnt + cnt * (cnt - 1) / 2;
        return {lo, hi};
    };

    for(int len = n; ; len++) {
        if(len % 2 == 0) continue;
        // cout << "s : " << s << " len : " << len << endl;
        auto [c, start, max_cnt] = getc(len);
        // cout << "len : " << len << " c : " << c << " start : " << start << " max_cnt : " << max_cnt << endl;
        ll l = 0, r = max_cnt;
        if(c < 0) continue;
        while(l != r) {
            ll m = (l + r + 1) / 2;
            auto [lo, hi] = get_range(m, start, max_cnt);
            if(lo <= c) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        // cout << "l : " << l << endl;
        auto [lo, hi] = get_range(l, start, max_cnt);
        // cout << "lo : " << lo << " hi : " << hi << endl;
        if(c <= hi) {
            cout << len << '\n';
            return;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}