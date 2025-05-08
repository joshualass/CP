#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int n = s.size();
    int res = INT_MAX;

    if(count(s.begin(), s.end(), '1') == 0) res = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j <= n; j++) {
            res = min(res, (int) ( count(s.begin(), s.begin() + i, '1') + count(s.begin() + j, s.end(), '1') + count(s.begin() + i, s.begin() + j, '0')));
        }
    }

    cout << res << '\n';

    return 0;
}
