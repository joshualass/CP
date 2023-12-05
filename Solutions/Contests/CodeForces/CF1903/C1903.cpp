#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    ll total_score = 0;
    ll sum = 0;
    
    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    for(int i = n - 1; i >= 0; i--) {
        //2 options - start a new subarray or add to current subarray
        // ll add = sum;
        // sum += v[i];
        // cout << "i : " << i << " add : " << add << " sum : " << sum << '\n';
        // total_score += max(sum, sum + add);
        total_score = max(v[i] + total_score, total_score + sum + v[i]);
        sum += v[i];
    }
    cout << total_score << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}