#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;

    ll mindiff = LLONG_MAX;
    for(int i = 0; i < (1 << n); i++) {
        ll one = 0;
        ll two = 0;
        for(int t = 0; t < n; t++) {
            if((i >> t) & 1) {
                one += v[t];
            } else {
                two += v[t];
            }
        }
        // cout << i << " " << one << " " << two << "\n";
        mindiff = min(mindiff, abs(one-two));
    }
    cout << mindiff << "\n";

    return 0;
}