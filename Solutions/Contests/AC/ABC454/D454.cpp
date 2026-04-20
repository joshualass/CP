#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string a, b; cin >> a >> b;

    auto canon = [](string &s) -> string {
        string res = "";
        for(char c : s) {
            if(c == ')' && sz(res) >= 3 && res.substr(sz(res) - 3) == "(xx") {
                res.pop_back();
                res.pop_back();
                res.pop_back();
                res.append("xx");
            } else {
                res.push_back(c);
            }
        }
        return res;
    };

    cout << (canon(a) == canon(b) ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}