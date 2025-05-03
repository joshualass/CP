#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    multiset<ll> ms;
    for(ll &x : a) {
        cin >> x;
        ms.insert(x);
    }
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        cout << sum + (*--ms.end()) << " \n"[i == n - 1];
        sum += a[n-i-1];
        ms.erase(ms.find(a[n-i-1]));
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}