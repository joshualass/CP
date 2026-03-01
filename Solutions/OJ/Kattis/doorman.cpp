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
    int res = 0, cur = 0;
    for(char c : s) {   
        if(c == 'W') {
            cur++;
        } else {
            cur--;
        }
        if(abs(cur) == n + 2) {
            res--;
            break;
        }
        res++;
    }

    cout << res << '\n';

    return 0;
}
