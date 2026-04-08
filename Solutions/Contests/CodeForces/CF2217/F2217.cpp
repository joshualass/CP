#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int inf = 1e9;

void solve() {
    
    int x1, x2; cin >> x1 >> x2;

    //count the number of ways to choose y + z < x2 such that y ^ z = t.
    auto get_ways = [&](int t) -> int {
        if(t >= x2) return 0;
        int sum = t;
        int ways = 0, shift = 0;
        for(int bit = 20; bit >= 0; bit--) {
            if(((t >> bit) & 1) == 0) {
                ways *= 2;
                if(sum + (1 << (bit + 1)) < x2) {
                    sum += 1 << (bit + 1);
                    ways++;
                }
            } else {
                shift++;
            }
        }
        return (ways + 1) << shift;
    };

    int b = -1, bw = inf;
    for(int i = 0; i < x1; i++) {
        int tw = get_ways(i);
        // cout << "i : " << i << " x1 : " << x1 << " x2 : " << x2 << " tw : " << tw << endl;
        if(tw < bw) {
            b = i;
            bw = tw;
        }
    }

    cout << b + 1 << " " << x1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}