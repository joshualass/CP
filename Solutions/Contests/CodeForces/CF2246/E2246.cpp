#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    cout << "1" << endl;
    int o; cin >> o;
    if(o == 1) {
        int first = rng() % (1 << 29);
        int second = first;
        while(second == first) second = rng() % (1 << 29);
        int m0 = 1 + (first << 1);
        int m1 = (second << 1);
        cout << m0 << " " << m1 << endl;
        int r; cin >> r;
        if((r >> 1) == first) {
            cout << "0" << endl;
        } else if((r >> 1) == second) {
            cout << "1" << endl;
        } else {
            cout << (r & 1) << endl;
        }
    } else {
        if((o & 1) == 0) {
            //& operation with first bit 0
            int m0 = 0, m1 = 1;
            cout << m0 << " " << m1 << endl;
            int r; cin >> r;
            cout << (r & 1) << endl;
        } else {
            int bit = -1;
            for(int i = 1; i < 30; i++) {
                if((o >> i) & 1) {
                    bit = i;
                }
            }
            assert(bit != -1);
            int m0 = 0, m1 = 1 << bit;
            cout << m1 << " " << m0 << endl;
            int r; cin >> r;
            cout << ((r >> bit) & 1) << endl;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ld p = 1 / (ld) ((1LL) << 28);

    // ld res = 1;
    // for(int i = 0; i < 1e6; i++) res *= 1 - p;

    // cout << res << endl;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}