#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int MAXN = 2e6;
ll pc[MAXN + 1];

void solve() {
    ll n; cin >> n;
    cout << pc[n] * 4 % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //num 0 children, 1 children
    array<ll,2> a = {1,0};
    pc[0] = 0;
    for(int n = 2; n <= MAXN; n++) {
        array<ll,2> next = {(a[0] + a[1] * 2) % MOD, a[0] % MOD};
        ll add = a[1] % MOD;
        pc[n] = add % MOD;
        if(n >= 3) {
            pc[n] = (pc[n] + pc[n-3]) % MOD;
        }
        a = next;
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}