#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int cnt(vector<int> a) {
    int res = 0;
    for(int i = 0; i < sz(a); i++) {
        for(int j = i + 1; j <= sz(a); j++) {
            int x = 0;
            for(int k = i; k < j; k++) {
                x ^= a[k];
            }
            if(x == 0){
                res ++;
            }
        }
    }
    return res;
}

void solve() {
    
    int n; cin >> n;
    vector<int> res;
    for(int i = 1; ; i++) { 
        int tz = __builtin_ctz(i);
        int x;
        if(tz) {
            x = 1 << (tz - 1);
        } else {
            x = 0;
        }
        if(x > n) break;
        res.push_back(x);
    }

    cout << sz(res) << '\n';
    cout << res << '\n';

    // cerr << "len : " << sz(res) << " f(a) : " << cnt(res) << " delta : " << sz(res) - cnt(res) << '\n';

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