#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(a.empty() || x != a.back()) {
            a.push_back(x);
        }
    }

    int res = 0;
    for(int i = 0; i < a.size(); i++) {
        int ok = (i == 0 || a[i] > a[i-1]) && (i == a.size() - 1 || a[i] > a[i+1]);
        res += ok;
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