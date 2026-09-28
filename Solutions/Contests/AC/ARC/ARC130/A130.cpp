#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string str; cin >> str;
    ll ans = 0;
    ll cnt = 0;
    for(int i = 0; i < n - 1; i++) {
        if(str[i] == str[i+1]) {
            cnt++;
        } else {
            ans += cnt * (cnt + 1) / 2;
            cnt = 0;
        }
    }
    ans += cnt * (cnt + 1) / 2;
    cout << ans << '\n';

    return 0;
}