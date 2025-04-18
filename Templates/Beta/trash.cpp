#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "35 35\n";
    for(int i = 0; i < 35; i++) {
        cout << (1LL << i) << " \n"[i == 34];
    }

    return 0;
}
