#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> res(31);
    for(int bit = 0; bit < 30; bit++) {
        if((n >> bit) & 1) {
            if(res[bit] == 1) { //1 at this position and one here
                res[bit] = 0;
                res[bit+1] = 1;
            } else {
                if(bit != 0 && res[bit-1] == 1) {
                    res[bit-1] = -1;
                    res[bit+1] = 1;
                } else {
                    res[bit] = 1;
                }
            }
        }
    }
    cout << 31 << '\n';
    for(int i = 0; i < 31; i++) {
        cout << res[i] << " \n"[i == 30];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}