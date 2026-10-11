#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    srand(chrono::steady_clock::now().time_since_epoch().count());

    int n; cin >> n;
    for(int i = 1; i < n; i++) {
        cout << rand() % n + 1 << " \n"[i == n-1];
    }

    return 0;
}