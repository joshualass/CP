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
    vector<int> ml(n),mr(n);
    ml[0] = a[0], mr[n-1]=a[n-1];

    for(int i = 1; i < n; i++) {
        ml[i] = max(ml[i-1],a[i]);
    }

    for(int i = n - 2; i >= 0; i--) {
        mr[i] = min(mr[i+1],a[i]);
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        int ok = 1;
        if(i) {
            if(ml[i-1] > a[i]) ok = 0;
        }
        if(i != n - 1) {
            if(mr[i+1] < a[i]) ok = 0;
        }
        res += ok;
    }

    cout << res << '\n';

    return 0;
}