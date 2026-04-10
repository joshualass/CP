#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> cnts(30);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        for(int j = 0; j < 30; j++) {
            if((x >> j) & 1) {
                cnts[j]++;
            }
        }
    }

    int g = 0;
    for(int i = 0; i < 30; i++) {
        g = gcd(g, cnts[i]);
    }

    for(int i = 1; i <= n; i++) {
        if(g % i == 0) {
            cout << i << " ";
        }
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}