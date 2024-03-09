#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    vector<ll> s1;
    vector<ll> s2;
    s1.push_back(1);
    s2.push_back(1);

    while(s2.back() < n && s1.size() < k) {
        s2.push_back(s2.back() * k + 1);
        s1.push_back(s1.back() * k);
    }

    ll l = 0, r = 1e9;
    ll maxzero = s1.back();
    // cout << "max zero : " << maxzero << '\n';
    while(l != r) {
        ll m = (l + r + 1) / 2;
        ll zerocount = 0;
        ll temp = m;
        for(int i = s1.size() - 1; i >= 0; i--) {
            while(temp >= s2[i]) {
                temp -= s2[i];
                zerocount += s1[i];
                if(zerocount >= maxzero) break;
            }
        }
        // cout << "0s : " << zerocount * k << " 1s : " << m << '\n';
        if(min(zerocount,maxzero) * k + m <= n) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';

    return 0;
}