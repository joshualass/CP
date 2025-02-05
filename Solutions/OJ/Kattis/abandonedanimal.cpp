#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<set<string>> a(n);
    for(int i = 0; i < k; i++) {
        int b; cin >> b;
        string it; cin >> it;
        a[b].insert(it);
    }
    int m; cin >> m;
    vector<string> b(m);
    for(auto &x : b) cin >> x;
    int p = 0;
    vector<int> f(m), r(m);
    for(int i = 0; i < n; i++) {
        while(p != m && a[i].count(b[p])) {
            f[p] = i;
            p++;
        }
    }

    p = m - 1;
    for(int i = n - 1; i >= 0; i--) {
        while(p != -1 && a[i].count(b[p])) {
            r[p] = i;
            p--;
        }
    }

    if(p >= 0) {
        cout << "impossible\n";
        return 0;
    }
    if(f == r) {
        cout << "unique\n";
    } else {
        cout << "ambiguous\n";
    }

    return 0;
}