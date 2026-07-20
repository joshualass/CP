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
    if(n == 2) {
        cout << "-1\n";
    } else {
        vector<ll> res;
        for(int i = 0; i < n; i++) {
            if(i < 3) {
                res.push_back(i + 1);
            } else {
                res.push_back(res.back() * 2);
            }
        }
        cout << res << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}