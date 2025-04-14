#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    array<int,3> res = {};
    for(int i = 1; i < s.size(); i++) {
        for(int j = 0; j < 3; j++) {
            char c = s[i], p, n;
            if(j == 0) {
                if(i == 1) {
                    p = s[i-1];
                } else {
                    p = 'U';
                }
                n = 'U';
            } else if(j == 1) {
                if(i == 1) {
                    p = s[i-1];
                } else {
                    p = 'D';
                }
                n = 'D';
            } else {
                p = s[i-1], n = c;
            }
            if(p != c) res[j]++;
            if(c != n) res[j]++;
        }
    }

    for(int x : res) cout << x << '\n';

    return 0;
}
