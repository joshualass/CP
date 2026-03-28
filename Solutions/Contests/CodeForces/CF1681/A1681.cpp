#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    int mxa = 0, mxb = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        mxa = max(mxa, x);
    }
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        mxb = max(mxb, x);
    }

    if(mxa == mxb) {
        cout << "Alice\nBob\n";
    } else if(mxa > mxb) {
        cout << "Alice\nAlice\n";
    } else {
        cout << "Bob\nBob\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}