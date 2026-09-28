#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    v.push_back(v.front());

    ll diff = 0;

    for(int i = 0; i < n; i++) {
        diff += abs(v[i] - v[i+1]);
    }

    cout << max(*max_element(v.begin(), v.end()), diff/2) << '\n';

    return 0;
}