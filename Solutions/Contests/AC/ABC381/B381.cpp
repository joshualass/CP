#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    if(s.size() % 2 == 1) {
        cout << "No\n";
        return 0;
    }    

    set<char> vis;
    int ok = 1;
    for(int i = 0; i < s.size(); i += 2) {
        if(s[i] != s[i+1]) ok = 0;
        if(vis.count(s[i])) ok = 0;
        vis.insert(s[i]);
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}