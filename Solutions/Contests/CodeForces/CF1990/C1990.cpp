#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void get_MADDDD(vector<ll> &a, ll &res) {

    res += accumulate(a.begin(), a.end(), 0LL);
    int n = a.size();

    vector<bool> vis(n + 1);
    vector<ll> b(n);

    for(int i = 0; i < n; i++) {
        if(i != 0) {
            b[i] = b[i-1];
        }
        if(vis[a[i]] == 1) {
            b[i] = max(b[i], a[i]);
        }
        vis[a[i]] = 1;
    }
    swap(a,b);
}

void solve() {
    int n; cin >> n;
    ll res = 0;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    get_MADDDD(a, res);
    //after 1 MAD, array is nondecreasing
    get_MADDDD(a, res);
    //after 2 MADs, duplicates in array are removed

    for(int i = n - 1; i >= 0; i--) {
        res += (n - i) * a[i];
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