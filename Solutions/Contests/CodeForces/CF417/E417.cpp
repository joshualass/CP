#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int cnt = 0;
//     set<ll> sq;
//     for(int i = 0; i <= 1e6; i++) {
//         sq.insert(1LL * i * i);
//     }

//     set<int> bad;

//     for(int i = 0; i < 5e4; i++) {
//         int f = 0;
//         for(int j = 0; j < 5e4; j++) {
//             if(sq.count(i + 1LL * j * j)) {
//                 cnt++;
//                 f = 1;
//                 break;
//             }
//         }
//         if(!f) bad.insert(i);
//     }

//     cout << cnt << '\n';

//     for(int b : bad) cout << b << '\n';

//     return 0;
// }