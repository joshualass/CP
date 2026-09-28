#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<ll,int>> v(n);
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = {num,i};
    }
    ll sum = 0;
    
    sort(v.begin(),v.end());
    vector<bool> ismax(n);
    for(int i = n/2; i < n; i++) {
        sum += v[i].first;
        ismax[v[i].second] = true;
    }
    for(int i = 0; i < n; i++) {
        ismax.push_back(ismax[i]);
    }
    vector<pair<int,int>> dp(n * 2);
    int valid_rotation = -1;
    for(int i = 1; i < n * 2; i++) {
        if(i != 1) {
            if(dp[i-2].second > 0 || ismax[i] == 0 || ismax[i-1] == 0) { //can continue from previous 
                dp[i] = {dp[i-2].first + 2, dp[i-2].second + (ismax[i] ^ 1) + (ismax[i-1] ^ 1) - 1};
                if(dp[i].first == n) { //doesn't find all valid rotations ... just at least one :)
                    valid_rotation = i;
                    // cout << "valid i: " << i << "\n";
                }
            }
        } else {
            if(ismax[i] == 0 || ismax[i-1] == 0) {
                dp[i] = {2, (ismax[i] ^ 1) + (ismax[i-1] ^ 1)};
            }
        }
        // cout << "i: " << i << " first: " << dp[i].first << " second: " << dp[i].second << "\n";
    }

    cout << (valid_rotation - n + 1) % n << " " << sum << "\n";
    // cout << (n * 2 - valid_rotation) % n << " " << sum << "\n";

    return 0;
}