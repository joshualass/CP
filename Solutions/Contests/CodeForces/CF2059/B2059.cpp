#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int res = k / 2 + 1;
    if(n == k) {
        for(int i = 0; i < n; i++) {
            if((i & 1) && a[i] != (i + 1) / 2) {
                res = (i + 1) / 2;
                break;
            }
        }
    } else {
        res = 2;
        for(int i = 1; n - (i + 1) >= k - 2; i++) {
            if(a[i] != 1) res = 1;
        }
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

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
//     int n, k; cin >> n >> k;
//     int res = k / 2 + 1;
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         int minb = max(0, k - (n - (i + 1)) - 1);
//         int maxb = min(i, k - 1);
//         cout << "minb : " << minb << " maxb : " << maxb << '\n';
//         for(int j = minb; j <= maxb; j++) {
//             if((j & 1) && x != (j + 1) / 2) {
//                 res = min(res, (j + 1) / 2);
//                 break;
//             }
//         }
//     }
//     cout << res << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }