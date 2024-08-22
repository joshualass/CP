#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll getgrundy(ll a, ll k) {

    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int g = 0;
    for(int i = 0; i < n; i++) {
        ll a, k; cin >> a >> k;
        g ^= getgrundy(a,k);
    }

    cout << (g == 0 ? "Aoki" : "Takahashi") << '\n';

    return 0;
}