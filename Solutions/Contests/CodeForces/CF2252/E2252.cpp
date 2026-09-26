#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int mod = 1e9 + 7;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll ttfang(ll msb, vector<int> fixed) {
    ll res = 1LL << (msb - max(1, sz(fixed)));
    if(count(fixed.begin(), fixed.end(), 1) == sz(fixed)) {
        for(int cnt = sz(fixed); cnt <= msb; cnt++) {
            if(cnt & 1) {
                int rem = max(1LL, msb - cnt);
                res -= 1LL << (rem - 1);
            }
        }
    }
    for(int i = 0; i < sz(fixed); i++) {
        if(fixed[i] == 0) {
            if(i & 1) res = 0;
            break;
        }
    }
    // cout << "msb : " << msb << " fixed : " << fixed << " res : " << res << endl;
    return res;
}

void solve() {
    
    ll n; cin >> n;
    ll res = 0;

    int msb = 64 - __builtin_clzll(n);
    vector<int> fixed;
    fixed.push_back(1);

    for(int i = msb - 2; i >= 0; i--) {
        if((n >> i) & 1) {
            fixed.push_back(0);
            res += ttfang(msb, fixed);
            fixed.pop_back();
        }
        fixed.push_back((n >> i) & 1);
        res += ttfang(i + 1, {});
    }

    res += ttfang(msb, fixed);

    cout << res % mod << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int d = 1; d <= 100; d++) {
    //     for(int j = 1; j < d * 100; j++) {
    //         int a = j, b = j + d, c = j + d * 2;
    //         if((a ^ b ^ c) == 0) {
    //             cout << "d : " << bitset<10>{d} << " triple : " << bitset<10>{a} << " " << bitset<10>{b} << " " << bitset<10>{c} << endl;
    //         }
    //     }
    // }

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}