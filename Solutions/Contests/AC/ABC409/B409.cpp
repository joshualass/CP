#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.rbegin(), a.rend());

    int res = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] > i) res = i + 1;
    }

    cout << res << '\n';

    return 0;
}
