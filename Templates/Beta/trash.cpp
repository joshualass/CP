#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 200000;

    cout << n << '\n';
    for(ll i = 0; i < n; i++) {
        for(int j = 0; j < 25; j++) cout << rng() % 10;
        cout << '\n';
    }

    return 0;
}
