#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setprecision(10);

    int n; cin >> n;
    vector<vector<double>> m(n,vector<double>(n));
    for(auto &x : m) for(auto &y : x) cin >> y;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << (m[i][j] + m[j][i]) / 2 << " \n"[j == n - 1];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << (m[i][j] - m[j][i]) / 2 << " \n"[j == n - 1];
        }
    }

    return 0;
}