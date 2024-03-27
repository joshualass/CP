#include <bits/stdc++.h>
using namespace std;

short a [10000];
bool vis[10000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    short n; cin >> n;
    while(n != 0) {
        char c; cin >> c;
        for(short i = 0; i < n; i++) {
            cin >> a[i];
        }
        memset(vis, 0, sizeof(vis));
        bool ok = 1;
        for(short i = n - 1; i >= 0; i--) {
            vis[a[i]] = 1;
            for(short j = i - 2; j >= 0; j--) {
                short t = a[i-1] * 2 - a[j];
                if(t >= 0 && t < n && vis[t]) ok = 0;
            }
        }
        cout << (ok ? "yes" : "no") << '\n';
        cin >> n;
    }

    return 0;
}