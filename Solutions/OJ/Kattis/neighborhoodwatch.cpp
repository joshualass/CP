#include <iostream>
typedef long long ll;
typedef long double ld;
using namespace std;



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << "ja\n";
    std::print("fluff you!\n");

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     ll res = 1LL * n * (n + 1) / 2;

//     vector<int> a(n);
//     for(int i = 0; i < k; i++) {
//         int x; cin >> x;
//         a[x-1] = 1;
//     }

//     a.push_back(n);

//     int p = -1;
//     for(int i = 0; i <= n; i++) {
//         if(a[i]) {
//             ll dist = i - p;
//             res -= dist * (dist - 1) / 2;
//             p = i;
//         }
//     }

//     cout << res << '\n';

//     return 0;
// }
