#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));

    auto check = [&]() -> int {
        for(int i = 0; i < n; i++) {
            for(int j = 1; j < m; j++) {
                if(a[i][j-1] >= a[i][j]) return 0;
            }
        }
        for(int j = 0; j < m; j++) {
            for(int i = 1; i < n; i++) {
                if(a[i-1][j] >= a[i][j]) return 0;
            }
        }
        return 1;
    };

    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    if(n == 1 || m == 1) {
        cout << (check() ? "YES" : "NO") << '\n';
        return 0;
    }

    array<ll,2> b = {};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            b[(i + j) & 1] += a[i][j] - (i + j);
            a[i][j] = i + j;
        }
    }

    a[n-1][m-1] += b[(n - 1 + m - 1) & 1];
    ll rem = b[(n - 1 + m - 1 - 1) & 1];
    
    a[n-2][m-1] += rem / 2;
    a[n-1][m-2] += (rem + 1) / 2;

    cout << (check() ? "YES" : "NO") << '\n';

    return 0;
}
