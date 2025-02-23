#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<string,int> m;
    int res = 0;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        m[s]++;
        res = max(res, m[s]);
    }
    cout << res << '\n';
    return 0;
}