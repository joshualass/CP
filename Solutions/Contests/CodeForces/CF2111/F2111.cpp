#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
seems pretty obvious but two pitfalls that i fell in 

1) need to take gcd of p and s for this approach. we might start late or exclude some things if we don't. 
2) x vs y coordinate bad impl 
*/

void solve() {
    
    int p, s; cin >> p >> s;
    int g = gcd(p, s);

    p /= g;
    s /= g;

    int tp = p, ts = s;

    while(ts <= 50000) {
        if(tp >= 4 && tp % 2 == 0) {
            int x = ((tp / 2) + 1) / 2;
            int y = tp / 2 / 2;
            int left = ts - (x + y - 1);
            if(left >= 0 && left <= (x - 1) * (y - 1)) {

                cout << ts << '\n';
                for(int i = 0; i < x; i++) cout << i << " 0" << '\n';
                for(int i = 1; i < y; i++) cout << "0 " << i << '\n';

                for(int i = 1; i < x; i++) {
                    for(int j = 1; j < y; j++) {
                        if(left) {
                            cout << i << " " << j << '\n';
                            left--;
                        }
                    }
                }

                return;

            }
        }

        tp += p;
        ts += s;
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