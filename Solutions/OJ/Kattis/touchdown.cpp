#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    int cur = 20, down = 1, fd = 30;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;

        cur += x;

        if(cur <= 0) {
            cout << "Safety\n";
            return 0;
        }

        if(cur >= 100) {
            cout << "Touchdown\n";
            return 0;
        }

        if(cur >= fd) {
            fd = cur + 10;
            down = 1;
        } else {
            down++;
            if(down == 5) {
                break;
            }
        }
    }

    cout << "Nothing\n";

    return 0;
}
