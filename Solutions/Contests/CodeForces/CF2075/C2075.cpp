#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for(int &x : a) {
        cin >> x;
        if(x == n) x--;    
    }

    sort(a.begin(), a.end());

    ll res = 0;
    ll sum = 0;
    int p = m;

    for(int i = 0; i < m; i++) {
        while(p - 1 >= 0 && a[p-1] + a[i] >= n) {
            p--;
            sum += a[p];
        }
        ll cnt = m - p;
        ll add = sum + cnt * (a[i] - n + 1);
        // cout << "i : " << i << " cnt : " << cnt << " p : " << p << " sum : " << sum << " add : " << add << '\n';
        res += add;
        if(a[i] * 2 >= n) {
            res -= a[i] * 2 - n + 1;
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}