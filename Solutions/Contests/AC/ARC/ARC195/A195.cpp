#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    int p = 0;
    vector<int> aa, bb;
    for(int i = 0; i < m; i++) {
        while(p < n && a[p] != b[i]) p++;
        if(p < n) aa.push_back(p++);
    }

    p = n - 1;
    for(int i = m - 1; i >= 0; i--) {
        while(p >= 0 && a[p] != b[i]) p--;
        if(p >= 0) bb.push_back(p--);
    }

    reverse(bb.begin(), bb.end());
    cout << (aa.size() == m && aa != bb ? "Yes" : "No") << '\n';

    return 0;
}
