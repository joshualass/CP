#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> p(n+1);
    iota(p.begin(), p.end(), 0);
    int r = n;
    for(int i = 1; i < n; i++) {
        while(r > i) {
            ll add = (r - i) * 2;
            if(k - add >= 0) {
                swap(p[i], p[r]);
                k -= add;
                r--;
                break;
            }
            break;
        }
    }
    if(k == 0) {
        cout << "Yes\n";
        for(int i = 1; i <= n; i++) {
            cout << p[i] << " \n"[i == n];
        }
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}