#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    int res = 0;
    vector<vector<int>> a(n+1,vector<int>(n+1));
    for(int i = 0; i <= n; i++) {
        a[i][0] = 1 % k;
        a[i][i] = 1 % k;
        if(a[i][0] == 0) res ++;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            a[i][j] = (a[i-1][j-1] + a[i-1][j]) % k;
            if(a[i][j] == 0) res++;
        }
    }

    cout << res << '\n';

    return 0;
}