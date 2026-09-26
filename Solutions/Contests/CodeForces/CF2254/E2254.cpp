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
    multiset<ll> ms;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        ms.insert(x);
    }

    vector<ll> res;
    ll prev = 0;
    for(int i = 0; i < n; i++) {
        if(ms.lower_bound(-prev + 1) != ms.end()) {
            auto val = *ms.lower_bound(-prev + 1);
            res.push_back(prev + val);
            prev = res.back();
            ms.erase(ms.find(val));
        } else {
            break;
        }
    }

    if(sz(res) == n) {
        cout << res << '\n';
    } else {
        cout << "-1\n";
    }

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