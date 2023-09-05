#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> v(n);
    ll sum1 = 0;
    ll sum2 = 0;
    for(ll &x: v) {
        cin >> x;
        sum2 += x;
    }
    ll most = LLONG_MIN;
    for(int i = 0; i < n; i++) {
        sum2 -= v[i];
        sum1 += v[i] * v[i];
        most = max(most,sum2*sum1);
    }
    cout << most << "\n";

    return 0;
}