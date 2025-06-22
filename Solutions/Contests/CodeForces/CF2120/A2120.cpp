#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int l1, b1, l2, b2, l3, b3; cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;

    int area = l1 * b1 + l2 * b2 + l3 * b3;
    int len = sqrt(area);
    while(len * len < area) len++;
    while(len * len > area) len--;

    auto check2 = [](int l1, int b1, int l2, int b2, int tl, int tb) -> int {
        if(l1 == tl && l2 == tl && b1 + b2 == tb) return 1;
        if(b1 == tb && b2 == tb && l1 + l2 == tl) return 1;
        return 0;
    };

    int ok = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            if(l1 == len && check2(l2, b2, l3, b3, len, len - b1)) ok = 1;
            swap(l1, l2);
            swap(l2, l3);
            swap(b1, b2);
            swap(b2, b3);
        }

        swap(l1, b1);
        swap(l2, b2);
        swap(l3, b3);
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}