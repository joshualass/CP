#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    string t;
    int ok = 1;
    for(char c : s) {
        if(c == '.') {
            if(ok) {
                ok = 0; 
                t.push_back('o');
            } else {
                t.push_back('.');
            }
        } else {
            t.push_back('#');
            ok = 1;
        }
    }

    cout << t << '\n';

    return 0;
}
