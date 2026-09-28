#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string perm; cin >> perm;
    map<char,int> m;
    for(int i = 0; i < 26; i++) {
        m[perm[i]] = i;
    }

    int res = 0;
    for(int i = 1; i < 26; i++) {
        res += abs(m['A' + i] - m['A' + i - 1]);
    }

    cout << res << '\n';

    return 0;
}