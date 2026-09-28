#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    
    vector<vector<int>> mat(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            cin >> mat[i][j];
            mat[i][j]--;
        }
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        res = mat[max(res, i)][min(res,i)];
    }

    cout << res + 1 << '\n';

    return 0;
}