#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> order(n,vector<int>(8));
    for(auto &x : order) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    vector<vector<int>> dp(n+1,vector<int>(8)); //dp[i][j] if a priest i votes at position j, stores the final position
    for(int i = 0; i < 8; i++) {
        dp[n][i] = i;
    }

    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 8; j++) {
            pair<int,int> p = {9,-1};
            for(int b = 0; b < 3; b++) {
                if(order[i][dp[i+1][j ^ (1 << b)]] < p.first) {
                    p = {order[i][dp[i+1][j ^ (1 << b)]],dp[i+1][j ^ (1 << b)]};
                }
            }
            dp[i][j] = p.second;
        }
    }

    cout << "dp\n" << dp;

    // cout << dp[0][0] << '\n';
    int ans = dp[0][0];
    for(int bit = 2; bit >= 0; bit--) {
        cout << (((ans >> bit) & 1) ? 'Y' : 'N');
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}