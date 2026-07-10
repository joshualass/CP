#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int ppl = 0;

    for(int i = 0; i < n; i++) {
        char type; cin >> type;
        int cnt; cin >> cnt;
        if(type == 'P') {
            ppl += cnt;
        } else {
            int sub = min(ppl, cnt);
            cnt -= sub;
            ppl -= sub;
            cout << (cnt ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
