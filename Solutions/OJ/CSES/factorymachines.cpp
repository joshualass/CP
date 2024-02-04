#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ll n, t; cin >> n >> t;
    vector<ll> v(n); 
    for(auto &x: v) cin >> x;
    ll l = 1, r = 1e18;
    while(l < r) {
        ll m = (l + r) / 2;
        ll L = 0;
        for(auto x : v) {
            L += m/x;
            if(L >= t) break;
        }
        if(L < t) l = m + 1;
        else r = m;
    }
    cout << l;
}