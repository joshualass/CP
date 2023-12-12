#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k, g, m; cin >> k >> g >> m;

    int currg = 0, currm = 0;
    for(int i = 0; i < k; i++) {
        if(currg == g) {
            currg = 0;
        } else if(currm == 0) {
            currm = m;
        } else {
            int transfer = min(g - currg, currm);
            currg += transfer;
            currm -= transfer;
        }
    }
    cout << currg << " " << currm << "\n";
    return 0;
}