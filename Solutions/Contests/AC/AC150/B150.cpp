#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll a, b; cin >> a >> b;
    ll startA = a;
    if(a >= b) {
        cout << a - b << "\n";
        return;
    }
    //b is strictly greater
    ll best = (a - b % a) % a;
    // cout << "a: " << a << "\n";
    while(a != b) {
        if(b / a != b / (a+1)) {
            a++;
        } else {
            ll pow = 1;
            while(b / a == b / (a + pow * 2)) {
                pow *= 2;
            }
            a += pow;
            while(pow != 0) {
                if(b / a == b / (a + pow)) {
                    a += pow;
                }
                pow /= 2;
            }
        }
        // a++;
        // cout << "a: " << a << "\n";
        best = min(best, a - startA + (a - b % a) % a);
        // cout << "best: " << best << "\n";
    }
    cout << best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}