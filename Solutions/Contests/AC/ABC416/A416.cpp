#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r; cin >> n >> l >> r;
    string s; cin >> s;

    cout << (count(s.begin() + l - 1, s.begin() + r, 'o') == r - l + 1 ? "Yes" : "No") << '\n';    

    return 0;
}
