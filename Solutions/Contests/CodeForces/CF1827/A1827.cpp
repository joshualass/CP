#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;

    vector<int> a(n);
    vector<int> b(n);

    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    

    sort(b.begin(), b.end());
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        int l = -1, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(a[i] > b[m]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if(l >= 0) {
            p[l]++;
        }
    }

    ll ways = 1;
    ll cnt = 0;
    for(int i = n - 1; i >= 0; i--) {
        cnt += p[i];
        if(cnt) {
            ways = (ways * cnt) % MOD;
        } else {
            cout << "0\n";
            return;
        }
        cnt--;
    }

    cout << ways << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}