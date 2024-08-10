#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    int ans = -1;
    for(int i = 0; i <= n; i++) {
        int counter = 0;
        for(int t = 0; t < n; t++) {
            if(i >= v[t]) {
                counter++;
            }
        }
        if(n-counter == i) {
            ans = n-counter;
            break;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) {
        solve();
    }
    return 0;
}