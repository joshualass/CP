#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll p, q; cin >> p >> q;

    ll tot = p + q * 2;
    ll n = 1, m = 2e8;

    auto find_m = [&]() -> void {
        ll l = 0, r = 2e8;
        while(l != r) {
            ll mid = (l + r + 1) / 2;
            if(2 * n * mid + n + mid > tot) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        m = l;
    };

    auto find_n = [&]() -> void {
        ll l = 0, r = 2e8;
        while(l != r) {
            ll mid = (l + r) / 2;
            if(2 * mid * m + mid + m < tot) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        n = l;
    };

    while(n <= m) {
        ll score = 2 * n * m + n + m;
        if(score < tot) {
            find_n();
        } else if(score > tot) {
            find_m();

            
        } else {
            n++;
            find_m();
        }
        // cout << "n : " << n << " m : " << m << endl;
        score = 2 * n * m + n + m;
        if(score == tot && p >= abs(n - m)) {
            cout << n << " " << m << '\n';
            return;
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