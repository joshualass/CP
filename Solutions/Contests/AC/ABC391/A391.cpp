#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    while(s.size()) {
        if(s[0] == 'E') {
            cout << 'W';
        } else if(s[0] == 'W') {
            cout << 'E';
        } else if(s[0] == 'N') {
            cout << 'S';
        } else if(s[0] == 'S') {
            cout << 'N';
        }
        s.erase(s.begin());
    }
    cout << '\n';
    return 0;
}