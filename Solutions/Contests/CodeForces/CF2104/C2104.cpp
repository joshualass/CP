#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    int f = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'A') {
            int ok = 1;
            if(i == 0) {
                for(int j = i + 1; j + 1 < n; j++) {
                    if(s[j] == 'B') {
                        ok = 0;
                    }
                }
            } else if(i != n - 1) {
                for(int j = i + 1; j < n; j++) {
                    if(s[j] == 'B') {
                        ok = 0;
                    }
                }
            } else {
                if(s[0] == 'B') ok = 0;
            }
            if(ok) f = 1;
        }
    }

    cout << (f ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}