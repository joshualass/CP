#include <bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;
#define rep(i, a, b) for (int i = a; i < b; ++i)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<vector<int>> a(n, vector<int> (n));

        rep(i, 0, n) {
            rep(j, 0, n)
                cin >> a[i][j];
        }

        vector<int> ans;
        rep(i, 0, n) {
            if (i % 2 == 0) {
                // left to right
                rep(j, 0, n) {
                    ans.push_back(a[i][j]);
                }
            } else {
                for (int j = n-1; j > -1; --j) {
                    ans.push_back(a[i][j]);
                }
            }
        }

        int score = 0;
        rep(i, 1, n*n) {
            score += ans[i] < ans[i-1];
            score -= ans[i] > ans[i-1];
        }

        if (score < 0) {
            reverse(ans.begin(), ans.end());
        }

        for (auto x : ans)
            cout << x << " ";
        cout << endl;
        
    }

    return 0;
}