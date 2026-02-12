#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

ll f[2][1001][50001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    for(int i = 0; i < 2; i++) {
        // cout << "i : " << i << endl;
        for(int j = 0; j < n; j++) {
            // cout << "j : " << j + 1 << " ";
            for(int k = 0; k <= m; k++) {
                f[i][j+1][k] = f[i][j][k];
                if(k) f[i][j+1][k] = max(f[i][j+1][k], f[i][j+1][k-1]);
                if(k >= a[j][0]) {
                    f[i][j+1][k] = max(f[i][j+1][k], f[i][j][k - a[j][0]] + a[j][1]);
                }
                // cout << ' ' << f[i][j+1][k];
            }
            // cout << endl;
        }
        reverse(a.begin(), a.end());
    }

    ll mx = 0;
    for(int i = 0; i <= m; i++) mx = max(mx, f[0][n][i]);

    // cout << "mx : " << mx << endl;

    for(int i = 0; i < n; i++) {
        int fin = 0, fout = 0;
        for(int j = 0; j <= m; j++) {
            if(f[0][i][j] + f[1][n - i - 1][m - j] == mx) fout = 1;
            if(j >= a[i][0] && f[0][i][j - a[i][0]] + a[i][1] + f[1][n - i - 1][m - j] == mx) fin = 1;
        }

        // cout << "i : " << i << " fin : " << fin << " fout : " << fout << endl;

        if(fin && fout) {
            cout << 'B';
        } else if(fin) {
            cout << 'A';
        } else if(fout) {
            cout << 'C';
        } else {
            assert(0);
        }
    }

    cout << '\n';

    return 0;
}
