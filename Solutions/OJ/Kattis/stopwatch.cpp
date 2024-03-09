#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    if(n & 1) {
        cout << "still running\n";
        return 0;
    }
    int ans = 0;
    for(int i = 0; i < n; i+= 2) {
        int a, b; cin >> a >> b;
        ans += b - a;
    }
    cout << ans << '\n';
    return 0;
}