#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MOD = 998244353;

map<ll,ll> m;

void recur(ll n) {
    ll lo = n / 2;
    ll hi = (n + 1) / 2;
    ll ans = 1;
    if(m.count(lo) == 0) {
        recur(lo);
    }
    if(m.count(hi) == 0) {
        recur(hi);
    }
    m[n] = m[lo] * m[hi] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;

    ll n; cin >> n;
    if(m.count(n) == 0) {
        recur(n);
    }
    cout << m[n] << '\n';

    return 0;
}