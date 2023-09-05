#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

ld dw, da;
const ld pi = 3.14159265359;

ld func(ld x) {
    // cout << "x: " << x << " first: " << (x / 2) * x * dw << " second: " << (x + (1 - x) / 2) * (1 - x) * da << "\n";
    return ((x / 2) * x * dw + (x + (1 - x) / 2) * (1 - x) * da) / (x * dw + (1 - x) * da);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ld h, r;
    cin >> h >> r >> da >> dw;
    
    ld a = 0; 
    ld b = 1;

    while(abs(func((a + (b - a) / 3)) - func(a + (b - a) * 2 / 3)) > 1e-19) {
        ld c = (a + (b - a) / 3);
        ld d = a + (b - a) * 2 / 3;
        // cout << "a: " << a << " b: " << b << '\n';
        // cout << "c: " << c << " d: " << d << '\n';
        // cout << "func c " << func(c) << " func(d) " << func(d) << "\n\n";
        if(func(c) <= func(d)) {
            b = d;
        } else {
            a = c;
        }
    }
    // cout << a << '\n';
    cout << fixed << setprecision(10) << h * a << '\n';
    return 0;
}