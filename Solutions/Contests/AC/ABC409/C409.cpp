#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l; cin >> n >> l;
    vector<int> a(l);
    ll cur = 0;
    a[cur]++;
    for(int i = 1; i < n; i++) {
        int x; cin >> x;
        cur = (cur + x) % l;
        a[cur]++;
    }

    // cout << "a : " << a << '\n';

    ll res = 0;
    if(l % 3 == 0) {
        for(int i = 0; i < l / 3; i++) {
            // cout << "i : " << i << " ttfang : " << 1LL * a[i] * a[i + l / 3] + a[i + l * 2 / 3] << '\n';
            res += 1LL * a[i] * a[i + l / 3] * a[i + l * 2 / 3];
        }
    }

    cout << res << '\n';

    return 0;
}
