#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    bitset<N> dp {};
    bitset<N> reachable {};
    vector<ll> v(N);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<ll> sums(N);
    sums[0] = v[0];
    for(int i = 1; i < N; i++) {
        sums[i] = v[i] + sums[i-1];
    }
    
    dp[0] = 1;
    reachable |= dp;
    
    for(int i = 0; i < n; i++) {
        dp |= dp << v[i];
        dp[i] = 0;
        reachable |= dp;
    }
    ll ans = 0;
    for(int i = 0; i < N; i++) {
        if(reachable[i]) {
            ans = max(ans, sums[i] - i);
        }
    }
    
    cout << ans << "\n";

    return 0;
}
