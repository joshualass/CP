#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll a, b, c, k; cin >> a >> b >> c >> k;

    auto getr = [&](int num) -> array<int,2> {
        int start = 1;
        for(int i = 2; i <= num; i++) start *= 10;
    
        int stop = start * 10;
        return {start, stop - 1};
    };

    auto [astart, astop] = getr(a);
    auto [bstart, bstop] = getr(b);
    auto [cstart, cstop] = getr(c);

    

    for(int i = astart; i <= astop; i++) {
        int minb = max(cstart - i, bstart);
        int maxb = min(cstop - i, bstop);
        int cnt = max(0, maxb - minb + 1);
        if(cnt >= k) {
            int b = minb + k - 1;
            cout << i << " + " << b << " = " << i + b << '\n';
            return;
        } else {
            k -= cnt;
        }
    }    

    cout << "-1\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}