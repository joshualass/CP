#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// https://math.stackexchange.com/questions/11002/cn-p-even-or-odd

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto nck_is_even = [](int n, int k) -> bool {
        return k & (n - k);
    };

    int n; cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(nck_is_even(n - 1, i) == 0) res ^= x;
    }

    cout << res << '\n';

    return 0;
}