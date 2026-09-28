#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t; cin >> s >> t;
    int ok = 1;

    for(int i = 1; i < s.size(); i++) {
        if(s[i] <= 'Z') {
            if(t.find(s[i-1]) == std::string::npos) ok = 0;
        }
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}
