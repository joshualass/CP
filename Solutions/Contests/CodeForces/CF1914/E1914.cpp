#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> b(n);

    for(auto &x : a) cin >> x;
    for(auto &y : b) cin >> y;

    vector<array<ll,3>> adds(n);
    for(int i = 0; i < n; i++) {
        adds[i] = {a[i] + b[i], a[i], b[i]};
    }
    sort(adds.rbegin(), adds.rend());

    ll score = 0;
    for(int i = 0; i < n; i++) {
        if(i & 1) {
            score -= adds[i][2] - 1;
        } else {
            score += adds[i][1] - 1;
        }
    }
    cout << score << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}