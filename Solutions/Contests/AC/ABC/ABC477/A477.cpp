#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<char,char> m = {
        {'B', 'Y'},
        {'Y', 'R'},
        {'R', 'B'}
    };

    char c; cin >> c;
    cout << m[c] << '\n';

    return 0;
}
