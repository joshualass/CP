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
    int n; cin >> n;
    vector<int> b(n-1);
    for(int &x : b) cin >> x;

    vector<int> a(n);
    for(int i = 1; i < n - 1; i++) {
        a[i] = b[i - 1] | b[i];
    }
    // cout << " b : " << b << "\n";
    a[0] = b[0];
    a[n-1] = b[n-2];
    bool ok = 1;
    for(int i = 0; i < n - 1; i++) {
        if((a[i] & a[i+1]) != b[i]) ok = 0;
    }

    if(ok) {
        for(int i = 0; i < n; i++) {
            cout << a[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}