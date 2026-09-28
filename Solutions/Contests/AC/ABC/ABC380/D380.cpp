#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        k--;
        ll d = k / s.size();
        char c = s[k % s.size()];
        if(__builtin_popcountll(d) & 1) {
            if(c >= 'a') {
                c -= 'a';
                c += 'A';
            } else {
                c -= 'A';
                c += 'a';
            }
        }
        cout << c << " \n"[i == q - 1];
    }

    return 0;
}