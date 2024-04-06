#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int one = count(s.begin(), s.end(), '1');
    if(one % 2 == 0 && (one != 2 || s.find("11") == std::string::npos)) {
        cout<< "Yes\n";
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}