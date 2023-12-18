#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    string str; cin >> str;
    string lo = ""; lo.push_back(str[0]);
    int i = 1;
    for(; i < str.size(); i++) {
        if(str[i] != '0') break;
        lo.push_back(str[i]);
    }
    string hi = str.substr(i);
    if(lo.size() == 0 || hi.size() == 0) {
        cout << "-1\n";
        return;
    }
    int l = stoi(lo);
    int h = stoi(hi);
    if(l >= h) {
        cout << "-1\n";
    } else {
        cout << l << " " << h << '\n';
    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}