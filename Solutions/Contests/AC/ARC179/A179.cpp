#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll sum = accumulate(a.begin(), a.end(), 0LL);

    if(k > 0) {
        cout << "Yes\n";
        for(int i = 0; i < n; i++) {
            cout << a[i] << " \n"[i == n - 1];
        }
    } else if(sum >= k) {
        reverse(a.begin(), a.end());
        cout << "Yes\n";
        for(int i = 0; i < n; i++) {
            cout << a[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "No\n";
    }

    return 0;
}