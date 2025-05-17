#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m, a, b; cin >> n >> m >> a >> b;

    auto get_moves = [&](int x, int y) -> int {
        int a = 0, b = 0;
        while(1 << a < x) a++;
        while(1 << b < y) b++;
        return a + b;
    };

    cout <<  min(get_moves(n, min(b, m - b + 1)), get_moves(min(a, n - a + 1), m)) + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}