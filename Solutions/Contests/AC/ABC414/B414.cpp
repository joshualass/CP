#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll len = 0;
    vector<pair<char, ll>> a(n);
    for(auto &x : a) {
        cin >> x.first >> x.second;
        len += x.second;
        if(len > 100) break;
    }

    // cout << "len : " << len << '\n';

    if(len > 100) {
        cout << "Too Long\n";
        return 0;
    }

    string res = "";
    for(auto x : a) res.append(string(x.second, x.first));
    cout << res << '\n';

    return 0;
}
