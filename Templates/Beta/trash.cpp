#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto f = [&](ld x, ld a) -> ld {
        return a * x * x * (1 - x);
    };

    ld a = 5;
    ld x = 0.2;

    cout << "0.2" << '\n';

    for(int i = 0; i < 10; i++) {
        cout << fixed << setprecision(10) << x << '\n';
        x = f(x, a);
    }

    x = 0.5;

    cout << "0.5\n";

    for(int i = 0; i < 100; i++) {
        cout << fixed << setprecision(10) << x << '\n';
        x = f(x, a);
    }

    return 0;
}
