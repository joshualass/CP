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
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
    }

    sort(a.begin(), a.end());
    vector<int> res(n);
    int l = 0, r = n - 1;
    while(l <= r) {
        if((a[r][0] == n - l) ^ (a[l][0] == n - 1 - r)) {
            if(a[r][0] == n - l) {
                res[a[r][1]] = r - l + 1;
                r--;
            } else {
                res[a[l][1]] = l - r - 1;
                l++;
            }
        } else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}