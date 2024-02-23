#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int cnt = 0;
    bool start = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == 1) {
            if(!start) {
                start = 1;
            } else {
                ans += cnt;
                cnt = 0;
                
            }
        } else {
            if(start) cnt++;
        }
    }   
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}