#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

bool isSquare(ll x) {
    ll y = (ll)sqrt(x);
    return y * y == x || (y-1) * (y-1) == x || (y+1) * (y+1) == x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    if(n % 2) {
        cout << n / 2 << " " << n / 2 + 1 << "\n";
        return 0;
    } else {
        for(ll i = 0; i < 1223456; i++) {
            if(isSquare(n + i * i)) {
                ll first = (ll)sqrt(n + i * i);
                ll second = (ll)sqrt(first * first - n);
                cout << second << " " << first << "\n";
                return 0;
            }
        }
    }
    cout << "impossible\n";
    return 0;
}