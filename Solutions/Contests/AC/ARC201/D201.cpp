#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, m; cin >> n >> m;

    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    sort(a.rbegin(), a.rend());
    sort(b.begin(), b.end());

    // cout << "a : " << a << '\n';
    // cout << "b : " << b << '\n';

    for(int i = 0; i < n; i++) b.push_back(b[i] + m);

    int lo = 0, hi = m - 1;
    while(lo != hi) {
        int mid = (lo + hi) / 2;

        // cout << "mid : " << mid << '\n';
        
        vector<int> pre(n * 2 + 1);
        int lp = 0, rp = 0;

        for(int i = 0; i < n; i++) {
        // for(int i = n - 1; i >= 0; i--) {
            int at_least = m - a[i];
            int at_most = at_least + mid;
            while(lp < n * 2 && b[lp] < at_least) lp++;
            while(rp < n * 2 && b[rp] <= at_most) rp++;

            int oslp = lp - i, osrp = rp - i;
            if(oslp < 0) {
                oslp += n;
                osrp += n;
            }

            // cout << "i : " << i << " a[i] : " << a[i] << " lp : " << lp << " rp : " << rp << '\n';

            assert(oslp <= osrp);

            pre[oslp]++;
            pre[osrp]--;

        }

        vector<int> p(n);
        int cur = 0;
        for(int i = 0; i <= n * 2; i++) {
            cur += pre[i];
            p[i % n] += cur;
        }

        int mx = *max_element(p.begin(), p.end());
        assert(mx <= n);

        if(mx == n) {
            hi = mid;
        } else {
            lo = mid + 1;
        }

    }

    cout << lo << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}