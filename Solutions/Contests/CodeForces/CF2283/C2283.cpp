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

void solve() {
    
    int n; cin >> n;
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        cur ^= i;
    }

    vector<int> res(n + 1);

    for(int bit = 29; bit > 0; bit--) {
        if(((cur >> bit) & 1) == 0 && (1 << (bit - 1)) <= n) {
            int x = (1 << (bit - 1));
            res[x] = 1;
            cur ^= 1 << bit;
            cur ^= 1 << (bit - 1);
        }
    }

    res.erase(res.begin());
    cout << res << '\n';

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