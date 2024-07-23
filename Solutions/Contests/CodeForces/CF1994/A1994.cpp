#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> res(n,vector<int>(m));
    if(n != 1) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> res[(i+1) % n][j];
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << res[i][j] << " ";
            }
            cout << '\n';
        }


    } else if(m != 1) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> res[i][(j+1) % m];
            }
        }
                for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << res[i][j] << " ";
            }
            cout << '\n';
        }
    } else {
        for(int i = 0; i < n * m; i++) {
            int trash; cin >> trash;
        }
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}