#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int inf = 1e9;

int costs[4001][4001], dp[4001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            int x = a[i], y = a[j];
            int time = max((j - i + 1) * 20, y + 20 - (x + 1800)) + 120;
            costs[i][j+1] = time;
        }
    }

    for(int i = 0; i <= n; i++) dp[i] = inf;
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + costs[j][i]);
        }
    }

    cout << dp[n] << '\n';

    return 0;
}
