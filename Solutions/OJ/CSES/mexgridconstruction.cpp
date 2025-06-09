#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int vis[300];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 300; k++) {
                vis[k] = 0;
            }
            for(int k = 0; k < i; k++) {
                vis[a[k][j]] = 1;
            }
            for(int k = 0; k < j; k++) {
                vis[a[i][k]] = 1;
            }
            for(int k = 0; k < 300; k++) {
                if(vis[k] == 0) {
                    a[i][j] = k;
                    break;
                }
            }
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }



    return 0;
}
