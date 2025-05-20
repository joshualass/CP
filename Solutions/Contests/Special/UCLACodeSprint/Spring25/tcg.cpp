#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 447; i++) {
        for(int j = 0; j < 447; j++) {
            cout << ((char)('a' + ((rand() % 26))));
        }
        cout << '\n';
    }

    return 0;
}
