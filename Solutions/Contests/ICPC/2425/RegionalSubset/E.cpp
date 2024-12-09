#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int solve(int n, int m) {
    ld epsilon = 1e-11;
    int ans1 = 0;
    int ans2 = 0;
    ld ptr = m;
    ld slope = (ld) (m) / (ld) n;
    // cout << "SLOPE : " << slope << "\n";
    for(int i = 0; i < n; i++){
        ptr -= slope;
        // cout << "PTR : " << ptr << "\n";
        {
            ld cptr = ptr - (i % 2 == 0? 0 : 1);
            ld amt = (cptr / 2.0) + epsilon;
            ans1 += (int) amt;
            // cout << "AMT : " << amt << "\n";
        }
        {
            ld cptr = ptr - (i % 2 == 1? 0 : 1);
            ld amt = (cptr / 2.0) + epsilon;
            ans2 += (int) amt;
        }
    }
    return max(ans1, ans2);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    int ans = max(solve(n, m), solve(m, n));
    cout << ans << "\n";

    return 0;
}