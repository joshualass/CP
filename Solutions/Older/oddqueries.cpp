#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {

        int n, q; cin >> n >> q;
        vector<ll> prefix(n+1);
        for(int i = 1; i <= n; i++) {
            ll num; cin >> num;
            prefix[i] = prefix[i-1] + num;
        }
        for(int i = 0; i < q; i++) {
            ll l, r, k; cin >> l >> r >> k;
            ll pref = prefix[r] - prefix[l-1];
            bool flip = true;
            if(((r - l + 1) * k) % 2 == pref % 2) {
                flip = false;
            }
            cout << (flip ^ (prefix[n] % 2) ? "YES" : "NO") << "\n";
        }


    }

    return 0;
}