#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll calcans(vector<ll> &v, ll width, ll K) {
    ll ans = 0;
    for(ll x : v) {
        ans += width * (K - 1);
        ans -= ((K - 1) * width - x) % K; 
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll R, C, K; cin >> R >> C >> K;
    
    vector<ll> a(R);
    vector<ll> b(C);

    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    if(reduce(a.begin(),a.end()) % K != reduce(b.begin(),b.end()) % K) {
        cout << "-1\n";
        return 0;
    }

    cout << min(calcans(a,C,K), calcans(b,R,K)) << '\n';

    return 0;
}