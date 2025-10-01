#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;
    cout << s.substr(a, n - b - a) << '\n';

    return 0;
}
