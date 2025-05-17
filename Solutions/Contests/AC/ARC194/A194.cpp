#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    array<ll,2> dp = {0, -inf}; //previous is removed, previous is not removed

    for(int i = 0; i < n; i++) {
        array<ll,2> ndp = {-inf,-inf};

        if(i) ndp[0] = dp[1] - a[i-1];
        ndp[1] = max(dp[0] + a[i], dp[1] + a[i]);

        dp = ndp;
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
