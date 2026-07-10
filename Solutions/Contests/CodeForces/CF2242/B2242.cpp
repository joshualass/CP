#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int phase = 1;

    int over = 0, under = 0;

    for(int i = 0; i < n; i++) {
        if(a[i] > phase) {
            over++;
        } else {
            under++;
        }
        if(under >= over && (phase != 1 || under == over || i + 1 < n && a[i+1] != 3)) {
            phase++;
            over = 0;
            under = 0;
            if(phase == 3 && i + 1 < n) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}