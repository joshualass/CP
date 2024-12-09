#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    vector<vector<double>> pmax(n+1,vector<double>(k+1));
    pmax[0][0] = 1;
    for(double i = 1; i <= n; i++) {
        for(double j = 1; j <= k; j++) {
            for(double l = 0; l <= k; l++) {
                pmax[i][max(j,l)] += pmax[i-1][l] / k;
            }
        }
    }

    double res = 0;
    for(int i = 1; i <= k; i++) {
        res += i * pmax[n][i];
    }

    cout << fixed << setprecision(6) << res << '\n';

    return 0;
}