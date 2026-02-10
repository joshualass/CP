#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    int vol = 0, play = 0;
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            vol++;
        } else if(type == 2) {
            vol = max(0, vol - 1);
        } else {
            play ^= 1;
        }
        cout << (vol >= 3 && play ? "Yes" : "No") << '\n';
    }

    return 0;
}
