#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    array<int,2> a = {};
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x & 1]++;
    }

    if(a[0] == 1 && a[1] == 1 || a[1] == 3 && a[0] == 0) {
        cout << "Larpity\n";
    } else {
        cout << "Moggity\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}