#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    ll best = LLONG_MAX;
    ll curr = 0;
    for(int i = 0; i < n; i++) {
        curr += a[i];
    }
    best = min(best,curr + b[0] * n);
    curr = 0;
    for(int i = 0; i < n; i++) {
        curr += b[i];
    }
    best = min(best,curr + a[0] * n);
    cout << best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}