#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;

    auto ask = [&](int i, int j) -> int {
        cout << "? " << i << " " << j << endl;
        int res; cin >> res;
        return res;
    };

    for(int i = n * 2; i > 4; i -= 2) {
        int test = ask(i, i - 1);
        if(test == 1) {
            cout << "! " << i << endl;
            return;
        }
    }

    int c1 = ask(1, 2);
    int c2 = ask(1, 3);
    int c3 = ask(2, 3);

    if(c1 || c2) {
        cout << "! " << 1 << endl;
        return;
    }
    if(c3) {
        cout << "! " << 2 << endl;
        return;
    }
    cout << "! " << 4 << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}