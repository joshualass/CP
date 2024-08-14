#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//BPE, use stack storing strength and id. 

void solve() {
    int n; cin >> n;
    
    ll res = 0;
    stack<array<ll,2>> s; //{strength, b}

    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        ll maxprev = 0;
        while(1) {
            while(s.size() && s.top()[0] <= a && s.top()[1] != b) {
                maxprev = max(maxprev, s.top()[0]);
                s.pop();
            }
            if(s.size() && s.top()[1] == b) {
                a += s.top()[0] - maxprev;
                s.pop();
            } else {
                break;
            }
        }
        s.push({a,b});
        res = max(res,a);
        cout << res << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}