#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll a, b, c; cin >> a >> b >> c;
    ll sum = a + b + c;
    for(int i = 0; i < 4; i++) {
        if(sum % (3 + i) == 0) {
            ll avg = sum / (3 + i);
            int ops = 0;
            bool flag = true;
            if(a % avg != 0 || b % avg != 0 || c % avg != 0) {
                flag = false;
            }
            ops = a / avg + b / avg + c / avg - 3;
            if(flag && ops == i) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}