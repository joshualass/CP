#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    k ^= n;

    set<int> skip;

    for(int bit = 29; bit >= 0; bit--) {
        if((k >> bit) & 1) {
            if((1 << bit) < n) {
                skip.insert(1 << bit);
            } else {
                cout << "NO\n";
                return;
            }
        }
    }

    skip.insert(0);

    cout << "YES\n";
    for(int i = 0; i < n; i++) {
        if(skip.count(i) == 0) cout << i << " ";
    }
    for(int x : skip) cout << x << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}