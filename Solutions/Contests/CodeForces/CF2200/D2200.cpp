#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, x, y; cin >> n >> x >> y;
    vector<int> a, b;
    for(int i = 0; i < n; i++) {
        int p; cin >> p;
        if(i < x) {
            a.push_back(p);
        } else if(i < y) {
            b.push_back(p);
        } else {
            a.push_back(p);
        }
    }    

    int lo = INT_MAX, idx = 0;
    for(int i = 0; i < sz(b); i++) {
        if(b[i] < lo) {
            lo = b[i];
            idx = i;
        }
    }

    rotate(b.begin(), b.begin() + idx, b.end());

    for(int x : a) {
        if(sz(b) && b[0] < x) {
            for(int y : b) cout << y << " ";
            b.clear();
        }
        cout << x << " ";
    }
    for(int y : b) cout << y << " ";
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}