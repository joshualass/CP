#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> dp(n + 1);
    for(int i = 0; i < n; i++) {
        int ops = count(a[i].begin(), a[i].end(), '#');
        int mp = INT_MAX;
        for(int j = n; j >= 0; j--) {
            mp = min(mp, dp[j]);
            dp[j] = ops + mp;
            if(j) {
                if(a[i][j-1] == '#') ops--;
                if(a[i][j-1] == '.') ops++;
            }
        }
    }

    cout << *min_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
