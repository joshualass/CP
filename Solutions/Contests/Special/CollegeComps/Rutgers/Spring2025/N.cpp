#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;

    vector<string> res;
    int c = 1;
    while(n) {
        if(n & 1) {
            res.push_back("A" + to_string(c));
        }
        if((n / 2) & 1) {
            res.push_back("B" + to_string(c));
        }
        n /= 4;
        c *= 2;
    }
    cout << res.size() << " ";
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}