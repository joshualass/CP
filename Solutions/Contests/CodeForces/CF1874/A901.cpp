#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll a, b, n; cin >> a >> b >> n;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        b += min(num,a-1);
    }
    cout << b << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}