#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bitset<2000> bs[2000][999]; //[col][value][row]
int mat[2000][2000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> mat[i][j];
            mat[i][j]--;
            bs[j][mat[i][j]][i] = 1;
        }
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        bitset<2000> currbs {};
        for(int j = 0; j < m; j++) {
            currbs ^= bs[j][mat[i][j]];
        }
        // cout << "for row i : " << i << " contrib : " << currbs.count() << '\n';
        res += currbs.count();
    }

    if(m & 1) {
        res -= n;
    }

    cout << res / 2 << '\n';

    return 0;
}