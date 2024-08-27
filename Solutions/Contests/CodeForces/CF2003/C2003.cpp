#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> cnts(26);
    for(char x : s) {
        cnts[x-'a']++;
    }
    string res = "";
    int x = n;
    for(int i = 0; i < 420420420; i++) {
        if(cnts[i % 26]) {
            res.push_back('a' + (i  % 26));
            cnts[i % 26]--;
            x--;
            if(x == 0) {
                break;
            }
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}