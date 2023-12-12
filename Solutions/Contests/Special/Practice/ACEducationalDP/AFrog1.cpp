#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;

int dp[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    fill(begin(dp), begin(dp) + N, 1e9);
    dp[0] = 0;
    for(int i = 1; i < n; i++) {
        if(i != 1) {
            dp[i] = dp[i-2] + abs(v[i] - v[i-2]);
        }
        dp[i] = min(dp[i], dp[i-1] + abs(v[i] - v[i-1]));
    }
    cout << dp[n-1] << "\n";
    return 0;
}