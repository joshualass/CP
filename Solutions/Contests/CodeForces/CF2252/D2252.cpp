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
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> d(n - 1);
    for(int i = 1; i < n; i++) {
        d[i-1] = a[i] - a[i-1];
    }

    int l = 0;
    for(int i = 1; i + 1 < n; i++) {
        if((a[i-1] & 1) != (a[i+1] & 1)) {
            sort(d.begin() + l, d.begin() + i);
            l = i;
        }
    }

    sort(d.begin() + l, d.end());
    for(int i = 1; i < n; i++) {
        a[i] = a[i-1] + d[i-1];
    }

    cout << a << '\n';

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