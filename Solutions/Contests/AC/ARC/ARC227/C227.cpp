#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0) {
            int ok = 1;
            for(int j = 1; (j + 1) * i <= n; j++) {
                if(s.substr(0, i) != s.substr(i * j, i)) {
                    ok = 0;
                }
            }
            if(ok) {
                cout << n / i << '\n';
                cout << i * i << '\n';
                for(int j = 0; j < i; j++) {
                    cout << s.substr(0, i);
                }
                return 0;
            }
        }
    }

    return 0;
}
