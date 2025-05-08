#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; cin >> n;
    vector<ll> a(1 << n);
    for(ll &x : a) cin >> x;
    sort(a.rbegin(), a.rend());

    ll res = LLONG_MIN;

    for(int i = 0; i <= n; i++) {
        res = max(res, accumulate(a.begin(), a.begin() + (1 << i), 0LL));
    }

    cout << res << '\n';

    return 0;
}