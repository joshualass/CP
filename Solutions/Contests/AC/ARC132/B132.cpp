#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    int oneidx = -1;
    int nidx = -1;

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == 1) {
            oneidx = i;
        }
        if(num == n) {
            nidx = i;
        }
    }

    // cout << min(oneidx, 2 + n - oneidx) << '\n';

    if((nidx + n - oneidx) % n == 1) { //n is after 1
        cout << min(oneidx + 2, n - oneidx);
    } else {//n comes before 1
        cout << min(oneidx, 2 + n - oneidx);
    }
    cout << endl;

    return 0;
}