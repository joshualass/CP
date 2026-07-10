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

    int l = 0, r = n - 1;
    int rev = 0;
    vector<int> res(n);
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == 'o') {
            rev ^= 1;
        }
        if(rev == 0) {
            res[r--] = i;
        } else {
            res[l++] = i;
        }
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}
