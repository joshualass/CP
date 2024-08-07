#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int MAXN = 1e6 + 1;
ll cnts[MAXN];
ll a[MAXN];

/*
Interesting solution, but I don't know where this falls under as math goes.
To me, I tried to use the principles of inclusion/exclusion. Because at heart, if we look at all items that divide to different 


*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    fill(begin(cnts), end(cnts), 1LL);
    fill(begin(a),end(a),0LL);
    
    ll n; cin >> n;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[num]++;
    }

    ll res = 0;

    for(int i = 2; i < MAXN; i++) {
        ll cnt = cnts[i];
        ll sum = 0;
        for(int j = 1; j * i < MAXN; j++) {
            sum += a[i * j];
            cnts[i * j] -= cnt;
        }
        res += cnt * sum * (sum - 1) / 2;
    }

    cout << n * (n - 1) / 2 - res << '\n';

    return 0;
}