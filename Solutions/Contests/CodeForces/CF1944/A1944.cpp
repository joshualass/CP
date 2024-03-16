#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n+1);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[num]++;
    }
    int ans = 0;
    // if(v[0] == 0) {

    // } else {
    //     for(int i = 0; i < n; i++) {
    //         if(v[i] < 2) {
    //             if(v[i] == 1) {
    //                 ans = i + 1;
    //             } else {
    //                 ans = i;
    //             }
    //             break;
    //         }
    //     }
    // }
    bool useone = 1;
    for(int i = 0; i <= n; i++) {
        if(v[i] < 2) {
            if(useone && v[i] == 1) {
                useone = 0;
            } else {
                ans = i;
                break;
            }
        }
    }
    cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}