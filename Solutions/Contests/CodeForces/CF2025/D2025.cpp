#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> dp(m + 1);
    vector<int> checks;
    int t = 0;

    auto addChecks = [&]() -> void {
        vector<int> pos(m+1),neg(m+1);
        for(auto check : checks) {
            if(check > 0) {
                pos[check]++;
            } else {
                neg[-check]++;
            }
        }
        for(int i = 1; i <= m; i++) {
            pos[i] += pos[i-1];
            neg[i] += neg[i-1];
        }

        for(int i = 0; i <= t; i++) {
            dp[i] += pos[i] + neg[t-i];
        }
        checks.clear();
    };

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num) {
            checks.push_back(num);
        } else {
            addChecks();
            vector<int> nextdp(m+1);
            for(int j = 0; j <= t; j++) {
                nextdp[j] = max(nextdp[j], dp[j]);
                nextdp[j+1] = max(nextdp[j+1], dp[j]);
            }
            swap(dp,nextdp);
            t++;
        }
    }

    addChecks();

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}