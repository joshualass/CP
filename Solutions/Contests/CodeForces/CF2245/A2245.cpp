#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    string s; cin >> s;
    if(k * 2 > n) {
        cout << "-1\n";
        return;
    }

    int ops = 0;
    for(int i = 0; i < k; i++) {
        ops += s[i] == 'L';
        ops += s[n - i - 1] == 'R';
    }

    cout << ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}