#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n; cin >> n;
    string s; cin >> s;
    ll c = n * (n + 1) / 2;
    int debt = 0;
    for(int i = n - 1; i >= 0; i--) {

        if(s[i] == '1' && i - debt - 1 >= 0) {
            c -= i + 1;
            debt++;
        } else {
            debt--;
            debt = max(0,debt);
        }
    }
    cout << c << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}