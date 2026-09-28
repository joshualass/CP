#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    cout << (count(s.begin(), s.end(), '1') == 1 && count(s.begin(), s.end(), '2') == 2 && count(s.begin(), s.end(), '3') == 3 ? "Yes" : "No") << '\n';

    return 0;
}