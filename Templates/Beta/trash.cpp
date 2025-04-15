#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll sum = 0;
    for(int i = 1; i <= 1e9; i++) sum += i;
    cout << sum << '\n';

    return 0;
}
