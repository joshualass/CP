#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, x; cin >> n >> x;

    auto mx_make_even = [&](int x) -> array<int,2> {
        if(x == 0) {
            return {0, 0};
        } else if(x == 1) {
            return {5, 2};
        } else if(__builtin_popcount(x) == 1) {
            return {x + 2, 2};
        } else {
            return {x, __builtin_popcount(x) & (~1)};
        }
    };

    auto mx_make_odd = [&](int x) -> array<int,2> {
        if(x == 0) {
            return {6, 3};
        } else {
            return {x, (__builtin_popcount(x) + 1) / 2 * 2 - 1};
        }
    };

    if(n == 1 && x == 0) {
        cout << "-1\n";
        return;
    }

    auto [sum, ms] = (n & 1 ? mx_make_odd(x) : mx_make_even(x));
    // cout << "sum : " << sum << " ms : " << ms << '\n';
    cout << sum + max(0, n - ms) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}