#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int cntss(string s) {
    set<string> ss;
    for(int i = 0; i < s.size(); i++) {
        for(int j = 1; i + j <= s.size(); j++) {
            ss.insert(s.substr(i,j));
        }
    }
    return ss.size();
}

void solve() {
    string s; cin >> s;
    for(int len = 2; len <= 4; len++) {
        for(int i = 0; i + len <= s.size(); i++) {
            if(cntss(s.substr(i,len)) % 2 == 0) {
                cout << s.substr(i,len) << '\n';
                return;
            }
        }
    }
    cout << "-1\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}