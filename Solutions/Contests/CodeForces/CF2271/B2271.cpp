#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }
    int f = 0;
    // for(auto [_, v] : m) {
    //     if(v == k * 2 - 1) f = 1;
    // }

    for(int i = 0; ; i++) {
        int v = m[i];
        // cout << "i : " << i << " v : " << v << endl;
        if(v < k * 2) {
            if(v == k * 2 - 1) {
                f = 1;
            }
            break;
        }
    }

    cout << (f ? "YES" : "NO") << '\n';

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