#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, g, b; cin >> r >> g >> b;
    string s; cin >> s;

    if(s == "Blue") {
        cout << min(r,g) << '\n';
    }
    if(s == "Red") {
        cout << min(g,b) << '\n';
    }
    if(s == "Green") {
        cout << min(r,b) << '\n';
    }
    return 0;
}