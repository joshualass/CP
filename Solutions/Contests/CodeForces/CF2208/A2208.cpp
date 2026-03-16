#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            x--;
            m[x]++;
        }
    }
    int ok = 1;
    for(auto [k, v] : m) if(v > n * (n - 1)) ok = 0;

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}