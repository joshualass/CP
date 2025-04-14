#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        string t; cin >> t;
        cin >> x;
    }
    sort(a.begin(), a.end());
    int res = INT_MAX;
    for(int i =1 ; i < n; i++) res = min(res, a[i] - a[i-1]);
    cout << res << '\n';

    return 0;
}
