#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    sort(v.begin(),v.end());
    ll prod = v[0]+1;
    for(int i = 1; i < n; i++) {
        prod *= v[i];
    }
    cout << prod << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}