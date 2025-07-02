#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    map<int,int> m;
    m[a[0]] = 1;

    sort(a.begin() + 1, a.begin() + n - 1);

    // cout << "a : " << a << '\n';

    for(int i = 1; i < n; i++) {
        // cout << "i : " << i << '\n';
        if((i == n - 1 || a[i] > a[0]) && m.lower_bound((a[i] + 1) / 2) != m.end()) {
            m[a[i]] = 1 + m.lower_bound((a[i] + 1) / 2)->second;
            // cout << "reachable w/ : " << m[a[i]] << '\n';
        }
    }

    cout << (m.count(a[n-1]) ? m[a[n-1]] : -1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}