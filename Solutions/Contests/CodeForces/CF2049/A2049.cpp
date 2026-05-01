#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int f = -1, l = -1;
    for(int i = 0; i < n; i++) {
        if(a[i]) l = i;
    }
    for(int i = n - 1; i >= 0; i--) {
        if(a[i]) f = i;
    }

    if(f == -1) {
        cout << "0\n";
        return;
    }

    int flag = 0;
    for(int i = f; i <= l; i++) {
        if(a[i] == 0) flag = 1;
    }

    cout << 1 + flag << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}