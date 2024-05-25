#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    vector<int> b;
    for(int i = 0; i < n; i++) {
        bool found = 0;
        for(int x : b) {
            if(a[i] % x == 0) found = 1;
        }
        if(!found) {
            b.push_back(a[i]);
            if(b.size() > 2) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}