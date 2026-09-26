#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

//decks are split into 2 subarrays :)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int p = 0;
    int s = 1;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x < p) {
            s++;
        }
        p = x;
    }

    int res = 0;
    while(1 << res < s) res++;
    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> dp;

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         int l = -1, r = sz(dp) - 1;
//         while(l != r) {
//             int m = (l + r + 1) / 2;
//             if(x < dp[m]) {
//                 l = m;
//             } else {
//                 r = m - 1;
//             }
//         }
//         if(l + 1 == sz(dp)) {
//             dp.push_back(0);
//         }
//         // cout << "i : " << i << " l : " << l << endl;
//         dp[l + 1] = x;
//     }

//     int res = 0;
//     while(1 << res < sz(dp)) res++;
//     cout << res << '\n';

//     return 0;
// }
