#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int h, w; cin >> h >> w;
    string s; cin >> s;

    int d = count(s.begin(), s.end(), 'D');
    int r = count(s.begin(), s.end(), 'R');

    ll res = 0;

    int lo = 0, hi = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'D') {
            lo++, hi++;
            d--;
        } else if(s[i] == 'R') {
            r--;
        } else {
            if(lo + 1 + d < h) {
                lo++;   
            }
            int c = i - hi;
            if(c + 1 + r < w) {

            } else {
                hi++;
            }
        }
        res += (lo - hi + 1);
    }
    cout << res + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}