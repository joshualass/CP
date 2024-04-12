#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    string res = "";
    res.push_back(s[0]);
    for(int i = 1; i < s.size(); i++) {
        if(s[i] != res.back()) {
            res.push_back(s[i]);
        }
    }   
    cout << res << '\n';
    return 0;
}