#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;

    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    if(n == 1) {
        cout << "1\n";
        return;
    }
    sort(v.begin(), v.end());
    ll curr_gcd = abs(v[1] - v[0]);
    for(int i = 2; i < n; i++) {
        // cout << "i : " << i << " gcd : " << curr_gcd << '\n';
        curr_gcd = gcd(curr_gcd, abs(v[i] - v[i-1]));
    }
    // set<ll> s(v.begin(), v.end());
    // cout << "curr_gcd : " << curr_gcd << '\n';
    ll a_np1 = -1;
    ll curr_num = v.back();
    for(int i = n - 1; i >= 0; i--) {
        if(v[i] != curr_num) break;
        curr_num -= curr_gcd;
        a_np1 = curr_num;
    }
    ll ops = 0;
    ll high_num = v.back();
    v.push_back(curr_num);
    for(int i = 0; i < v.size(); i++) {
        ops += (high_num - v[i]) / curr_gcd;
    }
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}