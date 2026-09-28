#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    cout << count(s.begin(), s.end(), 'j') + count(s.begin(), s.end(), 'i') << '\n';

    return 0;
}
