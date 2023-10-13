#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, m; cin >> n >> m;
    string strn, strm; cin >> strn >> strm;
    int ops = 0;
    while(strn.size() < strm.size()) {
        ops++;
        strn.append(strn);
    }
    if(strn.find(strm) != string::npos) {
        cout << ops << "\n";
        return;
    }
    ops++;
    strn.append(strn);
    if(strn.find(strm) != string::npos) {
        cout << ops << "\n";
        return;
    }
    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}