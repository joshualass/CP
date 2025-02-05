#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> a, b;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a.insert(x);
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        b.insert(x);
    }
    cout << (a.size() + b.size() >= 4 ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}