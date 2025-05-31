#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 1e9;

void solve() {
    
    int n; cin >> n;
    vector<int> dp(5001, inf);

    vector<int> a(n);
    int gg = 0;
    for(int &x : a) {
        cin >> x;
        dp[x] = 0;    
        gg = gcd(gg, x);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= 5000; j++) {
            int g = gcd(a[i], j);
            dp[g] = min(dp[g], dp[j] + 1);
        }
    }

    if(count(a.begin(), a.end(), gg)) {
        cout << n - count(a.begin(), a.end(), gg)<< '\n';
    } else {
        cout << n - count(a.begin(), a.end(), gg) + dp[gg] - 1 << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}