#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> a;

    for(int i = 1; i <= 6; i++) {
        for(int j = 0; j < 1 << i; j++) {
            string s;
            for(int k = 0; k < i; k++) {
                s.push_back(((j >> k) & 1) + '0');
            }
            a.push_back(s);
        }
    }

    cout << sz(a) << '\n';
    for(string s : a) {
        cout << sz(s) << '\n';
        cout << s << '\n';
    }

    return 0;
}
