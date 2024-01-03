#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string str; cin >> str;
    if(str.find("ab") != string::npos || str.find("ba") != string::npos) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}