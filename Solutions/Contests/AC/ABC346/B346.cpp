#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s = "wbwbwwbwbwbw";
    string res = "";
    for(int i = 0; i < 20; i++) {
        res.append(s);
    }

    int w, b; cin >> w >> b;
    bool ok = 0;
    for(int i = 0; i < s.size(); i++) {
        int wc = 0, bc = 0;
        for(int j = 0; j < w + b; j++) {
            if(res[i+j] == 'w') {
                wc++;
            } else {
                bc++;
            }
        }  
        if(wc == w && bc == b) ok = 1;
    }
    cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}