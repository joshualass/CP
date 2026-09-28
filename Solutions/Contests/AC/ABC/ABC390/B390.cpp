#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    auto get_r = [&](int i) -> array<int,2> {
        return array<int,2>{a[i+1] / gcd(a[i],a[i+1]), a[i] / gcd(a[i],a[i+1])};
    };

    int ok = 1;
    for(int i = 2; i < n; i++) {
        if(get_r(0) != get_r(i-1)) ok = 0;
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}