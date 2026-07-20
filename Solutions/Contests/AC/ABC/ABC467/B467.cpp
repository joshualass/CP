#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        string s; cin >> s;
        if(s == "keep") res += b - a;
    }
    cout << res << '\n';
    return 0;
}
