#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int s, c, k; cin >> s >> c >> k;
    int res = 0, cur = c, lo = -1;

    vector<int> a(s);
    for(int &x : a) cin >> x;

    sort(a.begin(), a.end());

    for(int i = 0; i < s; i++) {
        if(cur == c || a[i] - lo > k) {
            cur = 0;
            lo = a[i];
            res++;
        }
        cur++;
    }

    cout << res << '\n';

    return 0;
}
