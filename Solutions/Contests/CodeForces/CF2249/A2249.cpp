#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<array<int,4>> a(n);
    for(int i = 0; i < n; i++) {
        for(auto &x : a[i]) cin >> x;
        a[i][0]--;
        a[i][2]--;
    }

    int res = 0;
    for(int i = 1; i <= n; i++) {
        int len = 0;
        for(int j = 0; j < n && len < i; j++) {
            int left_rank = len;
            int right_rank = i - 1 - len;
            if(a[j][0] <= left_rank && left_rank < a[j][1] || a[j][2] <= right_rank && right_rank < a[j][3]) continue;
            // cout << "i : " << i << " j : " << j << " ok" << endl;
            len++;
        }
        if(len == i) res = i;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}