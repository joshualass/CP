#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("movie.in","r",stdin);
    freopen("movie.out","w",stdout);

    int n, l; cin >> n >> l;
    vector<int> a(n);
    vector<set<int>> s(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int c; cin >> c;
        for(int j = 0; j < c; j++) {
            int num; cin >> num;
            s[i].insert(num);
        }
    }
    vector<int> dp(1 << n,-1);

    dp[0] = 0;
    int res = INT_MAX;
    for(int bm = 0; bm < 1 << n; bm++) {
        for(int b = 0; b < n; b++) {
            if(bm & (1 << b)) {
                int p = bm ^ (1 << b);
                if(dp[p] != -1) {
                    set<int>::iterator it = s[b].upper_bound(dp[p]);
                    if(it == s[b].begin()) continue;
                    it--;
                    dp[bm] = max(dp[bm], (*it) + a[b]);
                }
            }
        }
        if(dp[bm] >= l) {
            res = min(res, __builtin_popcount(bm));
        }
    }
    cout << (res == INT_MAX ? -1 : res) << '\n';
    return 0;
}