#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    if(m == 3 && n >= 5) {
        cout << "-1\n";
        return 0;
    }

    for(int i = 0; i < m; i ++) {
        cout << i << " " << (int)1e7 + i * i << '\n';
    }

    for(int i = 0; i < n - m; i++) {
        cout << i << " " << (int)-1e7 - i * i << '\n';
    }

    return 0;
}