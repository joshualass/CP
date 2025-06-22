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
    
    int n, m, k; cin >> n >> m >> k;

    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<int>> p(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            p[i][j] = (a[i-1][j-1] == 'g') + p[i-1][j] + p[i][j-1] - p[i-1][j-1];
        }
    }

    // for(int i = 0; i <= n; i++) cout << p[i] << '\n';

    auto get_p = [&](int l1, int l2, int r1, int r2) -> int {
        
        l1 = max(l1, 0);
        l2 = max(l2, 0);
        r1 = min(r1, n);
        r2 = min(r2, m);

        return p[r1][r2] - p[l1][r2] - p[r1][l2] + p[l1][l2];

    };

    int res = 0;
    k--;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                // cout << "i : " << i << " j : " << j << " val : " << get_p(0, 0, n, m) - get_p(i - k, j - k, i + k + 1, j + k + 1) << '\n';
                res = max(res, get_p(0, 0, n, m) - get_p(i - k, j - k, i + k + 1, j + k + 1));
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}