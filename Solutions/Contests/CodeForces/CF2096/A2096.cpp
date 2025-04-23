#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    vector<int> res(n);
    int lo = 1, hi = n;
    for(int i = n - 1; i > 0; i--) {
        if(s[i - 1] == '>') {
            res[i] = hi--;
        } else {
            res[i] = lo++;
        }
    }
    res[0] = lo;
    for(int x : res) cout << x << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}