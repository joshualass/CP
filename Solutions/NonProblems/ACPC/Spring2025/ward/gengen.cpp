#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int xlen = 5e8; xlen <= 2e9; xlen += 5e8) {
        for(int ylen = 5e8; ylen <= 2e9; ylen += 5e8) {
            for(int x = -1e9; x + xlen <= 1e9; x += 5e8) {
                for(int y = -1e9; y + ylen <= 1e9; y += 5e8) {
                    cout << "gen " << 200000 << " " << x << " " << y << " " << x + xlen << " " << y + ylen << " > $\n";
                }
            }
        }
    }

    return 0;
}
