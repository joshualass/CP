#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, w, l; cin >> n >> w >> l;
    vector<int> v(w);
    for(int &x : v) {
        cin >> x;
        x--;
    }
    int lo = 1, hi = n;
    while(lo != hi) {
        int m = (lo + hi) / 2;
        int cnt = 0;
        int a = 0;
        int i = 0;
        while(a < n) {
            // cout << "a : " << a << " i : " << i << endl;
            while(i != w && v[i] < a) i++;
            if(i < w) {
                if(v[i] < a + m) {
                    a += m;
                } else {
                    a = v[i];
                }
            } else {
                a = n;
            }
            cnt++;
        }
        // cout << "m : " << m << " cnt : " << cnt << '\n';
        if(cnt <= l) {
            hi = m;
        } else {
            lo = m + 1;
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