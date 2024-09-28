
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // vector<array<int,2> > a(n), b(n);
    // for(int i = 0; i < n; i++) {
    //     cin >> a[i][0];
    //     a[i][1] = i;
    // }

    // for(int i = 0; i < n; i++) {
    //     cin >> b[i][0];
    //     b[i][1] = i;
    // }

    // sort(a.rbegin(),a.rend());
    // sort(b.rbegin(),b.rend());

    // if(n == 1) {
    //     cout << a[0][0] + b[0][0] << '\n';
    // }

    // int res = 0;
    // for(int i = 0; i < 2; i++) {
    //     for(int j = 0; j < 2; j++) {
    //         if(a[i][1] != b[j][1]) {
    //             res = max(res, a[i][0] + b[i][0]);
    //         }
    //     }
    // }

    // cout << res << '\n';

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    cout << (*max_element(a.begin(), a.end()) + *max_element(b.begin(), b.end())) << '\n';

    return 0;
}