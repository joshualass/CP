#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k; cin >> n >> k;
    
    int poss = (n - 1) * 2 <= k && k <= n * (n - 1) / 2 + n / 2 && k % 2 == 0;

    // cout << "n : " << n << " k : " << k << " poss : " << poss << endl;
    if(poss == 0) {
        cout << "-1\n";
        return;
    }

    vector<int> par(n);

    for(int i = 0; i < n; i++) {
        if(i == 0) {
            par[i] = -1;
        } else if(i == 1) {
            par[i] = 0;
        } else {
            par[i] = i - 2;
        }
    }

    ll cur = n * (n - 1) / 2 + n / 2;
    for(int i = n - 1; i > 1; i--) {
        if((cur - k) / 2 >= (i - 1) / 2) {
            cur -= (i - 1) / 2 * 2;
            par[i] = 0;
        } else {
            ll rem = (cur - k) / 2;
            par[i] -= rem * 2;
            cur -= rem * 2;
            break;
        }
    }

    // cout << "cur : " << cur << endl;

    assert((cur == k) == poss);

    for(int i = 1; i < n; i++) {
        cout << i + 1 << " " << par[i] + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}