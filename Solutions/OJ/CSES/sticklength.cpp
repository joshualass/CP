#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll calc(vector<ll> &v, ll height) {
    ll sum = 0;
    for(int i = 0; i < v.size(); i++) {
        sum += abs(v[i] - height);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll l = 0;
    ll r = 1e9;
    while((r - l) >= 3) {
        ll m1 = l + (r - l) / 3;
        ll m2 = l + (r - l) * 2 / 3;
        if(calc(v, m1) < calc(v, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }

    ll least = LLONG_MAX;
    for(int i = l; i <= r; i++) {
        least = min(least, calc(v,i));
    }
    cout << least << "\n";

    return 0;
}
