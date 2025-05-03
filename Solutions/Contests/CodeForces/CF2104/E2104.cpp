#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    string s; cin >> s;

    vector<int> dp(n + 1);
    vector<int> a(k, n);
    vector<set<int>> b(k);

    for(int i = 0; i < k; i++) b[i].insert(n);

    for(int i = n - 1; i >= 0; i--) {
        b[s[i] - 'a'].insert(i);
        int latest = i;
        for(int j = 0; j < k; j++) latest = max(latest, a[j]);
        // cout << "latest : " << latest << endl;
        dp[i] = 1 + dp[latest];
        a[s[i] - 'a'] = i;
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int c = -1;
        string t; cin >> t;
        for(char x : t) {
            if(c != n) {
                c = *b[x - 'a'].upper_bound(c);
            }
        }
        cout << dp[c] << '\n';
    }

    return 0;
}