#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll extendedEuclidean(ll a, ll b, ll& x, ll& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        ll x1, y1;
        ll d = extendedEuclidean(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        ll kids, candies; cin >> kids >> candies;
        ll d = gcd(kids,candies);
        if(d != 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        if(candies == 1) {
            if(kids != 1e9) {
                cout << kids + 1 << "\n";
            } else {
                cout << "IMPOSSIBLE\n";
            }
            continue;
        }
        ll x, y;
        d = extendedEuclidean(kids,candies,x,y);
        // cout << x << " " << y << " " << d << "\n";
        if(y <= 0) {
            y += kids;
            x -= candies;
        }
        if(y <= 1e9) {
            cout << y << "\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
        // cout << x << " " << y << " " << d << "\n";
        // d = extendedEuclidean(candies,kids,x,y);
    }

    return 0;
}