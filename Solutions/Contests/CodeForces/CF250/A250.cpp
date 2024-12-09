#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> res;
    int lo = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < 0) {
            cnt++;
        }
        if(cnt == 3) {
            res.push_back(i - lo);
            cnt = 1;
            lo = i;
        }
    }
    // for(int i = 2; i < n; i++) {
    //     if(a[i-2] < 0 && a[i-1] < 0 && a[i] < 0) {
    //         res.push_back(i - lo);
    //         lo = i;
    //         i++;
    //     }
    // }
    res.push_back(n-lo);
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

    return 0;
}