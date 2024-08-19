#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int getgrundy(ll a) {
    if(a < 6) {
        if(a == 0) {
            return 0;
        }
        if(a == 1) {
            return 1;
        }
        if(a >= 2 && a <= 3) {
            return 2;
        }
        if(a >= 4 && a <= 5) {
            return 3;
        }
    } else {
        ll lo = 6, length = 6;
        while(1) {
            if(1e18 / lo >= 6 && a >= (lo + length - 1) * 6 + 6) {
                lo = (lo + length - 1) * 6 + 6;
                length *= 12;
            } else {
                if(a < lo + length) {
                    return 0;
                }
                if(a < lo + length * 3) {
                    return 1;
                }
                if(a < lo + length * 7) {
                    return 2;
                }
                return 3;
            }
        }
    }   
}

void solve() {
    
    int n; cin >> n;
    int g = 0;

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        g ^= getgrundy(a);
    }

    // cerr << "g : " << g << '\n';

    cout << (g == 0 ? "Derek" : "Henry") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // const int N = 1e6 + 1;

    // vector<int> grundys(N);
    // for(int i = 1; i < N; i++) {
    //     set<int> s;
    //     for(int j = 0; j < 7; j++) {
    //         s.insert(j);
    //     }   
    //     for(int j = 2; j <= 6; j++) {
    //         s.erase(grundys[i / j]);
    //     }
    //     grundys[i] = *s.begin();
    // }

    // for(int i = 0; i < N; i++) {
    //     // cout << "i : " << i << " correct i : " << grundys[i] << " calculated i : " << getgrundy(i) << '\n';
    //     if(grundys[i] != getgrundy(i)) {
    //         cout << "i : " << i << " correct : " << grundys[i] << " calculated : " << getgrundy(i) << '\n';
    //         return 0;
    //     }
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}