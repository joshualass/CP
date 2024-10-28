#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n & 1) {
        cout << n << '\n';
        cout << "2 ";
        for(int i = 4; i < n - 1; i++) {
            cout << i << " ";
        }
        cout << "1 3 " << n - 1 << " " << n << '\n';
    } else {
        set<int> s;
        for(int i = 1; i <= n; i++) {
            s.insert(i);
        }
        int k = 0;
        vector<int> res;
        int ans = 0;
        while((1 << k) <= n) {
            res.push_back(1 << k);
            ans += (1 << k);
            s.erase(1 << k);
            int r = -1;
            if(k == 0) {
                r = 5;
            } else {
                r = (1 << (k+1)) - 1;
            }
            k++;
            if((1 << k) > n) {
                break;
            }
            res.push_back(r);
            s.erase(r);
        }
        cout << ans << '\n';
        for(int x : s) {
            cout << x << " ";
        }
        for(int i = 0; i < res.size(); i++) {
            cout << res[i] << " \n"[i == res.size() - 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}