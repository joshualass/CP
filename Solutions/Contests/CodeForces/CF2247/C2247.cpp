#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    
    if(a == b) {
        cout << "0\n";
    } else {
        int p = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] == 1 && b[i] == 0) p ^= 1;
        }
        if(p) {
            cout << "1\n";
        } else {
            if(accumulate(a.begin(), a.end(), 0) == 0 || accumulate(b.begin(), b.end(), 0) == n) {
                cout << "-1\n";
            } else {
                cout << "2\n";
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}