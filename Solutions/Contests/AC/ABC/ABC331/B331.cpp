#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, s, m, l; cin >> n >> s >> m >> l;
    int ans = INT_MAX;
    for(int i = 0; i * 6 <= n + 12; i++) {
        for(int j = 0; j * 8 + i * 6 <= n + 12; j++) {
            for(int k = 0; i * 6 + j * 8 + k * 12 <= n + 12; k++) {
                if(i * 6 + j * 8 + k * 12 >= n) {
                    ans = min(ans, i * s + j * m + k * l);
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}