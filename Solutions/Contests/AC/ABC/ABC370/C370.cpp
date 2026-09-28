#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t; cin >> s >> t;

    vector<string> res;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] > t[i]) {
            s[i] = t[i];
            res.push_back(s);
        }
    }

    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] < t[i]) {
            s[i] = t[i];
            res.push_back(s);
        }
    }

    cout << res.size() << '\n';
    for(auto x : res) cout << x << '\n';

    return 0;
}