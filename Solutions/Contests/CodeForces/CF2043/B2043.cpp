#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, d; cin >> n >> d;

    cout << "1 ";
    if(d % 3 == 0 || n >= 3) {
        cout << "3 ";
    }
    if(d == 5) {
        cout << "5 ";
    }
    if(d == 7 || n >= 3) {
        cout << "7 ";
    }
    if(d == 9 || n >= 6 || n >= 3 && d % 3 == 0) {
        cout << "9 ";
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}