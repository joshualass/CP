#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k, x; cin >> n >> k >> x;
    ll lb = k * (k + 1) / 2;
    ll ub = n * (n + 1) / 2 - ((n - k) * (n - k + 1) / 2);
    cout << (x >= lb && x <= ub ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}