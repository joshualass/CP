#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ld pi = acos(-1);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << "pi : " << pi << '\n';

    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> b(m);
    for(int &x : b) {cin >> x, x++;}

    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        b.push_back(ceil(x * sqrtl(2) / 2));
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int res = 0;
    int p = 0;
    for(int x : a) {
        if(p < b.size() && b[p] <= x) {
            res++;
            p++;
        }
    }

    cout << res << '\n';

    return 0;
}
