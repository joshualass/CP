#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int l; cin >> l;

    cout << (s.size() >= l ? "Yes" : "No") << '\n';

    return 0;
}
