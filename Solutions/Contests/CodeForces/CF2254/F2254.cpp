#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    auto canon = [](vector<int> a) -> vector<int> {
        for(int bit = 29; bit >= 0; bit--) {
            int cnt = 0;
            for(int i = 0; i < sz(a); i++) {
                cnt += (a[i] >> bit) & 1;
            }
            int tcnt = sz(a) - cnt + 1;
            if(tcnt > cnt) {
                for(int i = 0; i < sz(a); i++) {
                    if()
                }
            }
        }
    };

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}