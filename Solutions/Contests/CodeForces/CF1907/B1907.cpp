#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    string str; cin >> str;
    map<int,char> ups;
    map<int,char> los;

    for(int i = 0; i < str.size(); i++) {
        if(str[i] == 'b') {
            if(los.size()) {
                los.erase((*--los.end()).first);
            }
        } else if(str[i] >= 'a' && str[i] <= 'z') {
            los[i] = str[i];
        } else if(str[i] == 'B') {
            if(ups.size()) {
                ups.erase((*--ups.end()).first);
            }
        } else {
            ups[i] = str[i];
        }
    }
    los.insert(ups.begin(), ups.end());
    for(auto x : los) cout << x.second;
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}