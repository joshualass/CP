#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;

    bool ok = true;

    for(int i = 1; i < t.size(); i++) {
        if(t[i] == t[i-1]) ok = false;
    }
    if(t.front() != t.back()) ok = false;
    if(ok) {
        ok = true;
        for(int i = 1; i < s.size(); i++) {
            if(s[i] == s[i-1] && s[i] == t[0])
                ok = false;

        }        
        cout << (ok ? "Yes" : "No") << '\n';


    } else {
        ok = true;
        for(int i = 1; i < s.size(); i++) {
            if(s[i] == s[i-1]) ok = false;
        }        
        cout << (ok ? "Yes" : "No") << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}