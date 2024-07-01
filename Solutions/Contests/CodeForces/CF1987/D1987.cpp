#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
dp[i][j]
i - the i'th cake that Alice eats
j - in order for Bob to force Alice to make that the i'th cake, how many cakes he needs to eat before

*/

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
    vector<int> cakes(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        cakes[num - 1]++;
    }
    vector<int> cnts;
    for(int x : cakes) {
        if(x) cnts.push_back(x);
    }
    cnts.push_back(1e9);
    n = cnts.size();
    vector<vector<int>> dp(n+1,vector<int>(n+1, 1e9)); 
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {//Alice is eating the i'th cake
        for(int j = i; j <= n; j++) {//the tastiness of the i'th cake Alice eats
            //store the minimum number of cakes Bob has to eat for this to be possible if possible
            dp[i][j] = dp[i-1][j-1];
            if(dp[i][j-1] + cnts[j-1] < i) {
                dp[i][j] = min(dp[i][j], dp[i][j-1] + cnts[j-1]);
            }
            if(i > 1 && dp[i-1][j-2] + cnts[j-2] < i) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-2] + cnts[j-2]);
            }
            if(j == n && dp[i][j] < i) {
                cout << i - 1 << '\n';
                return;
            }
        }
    }    

    cout << "dp\n" << dp;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}