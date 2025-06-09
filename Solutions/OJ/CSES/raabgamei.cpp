#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, a, b; cin >> n >> a >> b;
    if(a + b > n || a && !b || b && !a) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    vector<array<int,2>> res;
    while(a + b < n) {
        res.push_back({n, n});
        n--;
    }

    for(int i = 0; i < a; i++) {
        res.push_back({n - i, n - i - b});
    }

    for(int i = 0; i < b; i++) {
        res.push_back({n - i - a, n - i});
    }

    for(auto x : res) cout << x[0] << " ";
    cout << '\n';
    for(auto x : res) cout << x[1] << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}