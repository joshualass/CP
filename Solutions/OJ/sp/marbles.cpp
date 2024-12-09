#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k; cin >> n >> k;
    ll V = k - 1, N = n - k;
    ll res = 1;
    if(V > N) swap(V,N);
    for(int i = 1; i <= N + V; i++) {
        ll d = -1;
        if(i > N) {
            d = i - N;
        } else {
            d = i;
        }
        if(res % d == 0) {
            res /= d;
            res *= i;
        } else {
            res *= i;
            res /= d;
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