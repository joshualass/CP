#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int l, r, n; cin >> l >> r >> n;

    int diff;

    for(int i = 29; i >= 0; i--) {
        if((r >> i) & 1) {
            if((l >> i) & 1) {
                diff = -1;
            } else {
                diff = i;
            }
            break;
        }
    }

    int resl, resr;
    if(diff == -1) {
        resl = 0, resr = 0;
        for(int i = 29; i >= 0; i--) {
            if(((r >> i) & 1) != ((l >> i) & 1)) {
                break;
            } else {
                resl += (((r >> i) & 1) << i);
            }
        }
        resr = resl;
    } else {
        resr = 1 << diff;
        resl = max(1 << (diff - 1), l);
    }

    vector<int> sl, sr;
    while(resl) {
        sl.push_back(resl & 1);
        resl >>= 1;
    }
    while(resr) {
        sr.push_back(resr & 1);
        resr >>= 1;
    }

    reverse(sl.begin(), sl.end());
    reverse(sr.begin(), sr.end());

    for(int i = 0; i < n; i++) {
        cout << (sl[i % sz(sl)] & (sr[i % sz(sr)]));
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