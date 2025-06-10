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

    set<int> s;
    int r = 0;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        if(i) s.erase(a[i-1]);
        while(r < n && s.count(a[r]) == 0) {
            s.insert(a[r++]);
        }
        res += r - i;
    }

    cout << res << '\n';

    return 0;
}
