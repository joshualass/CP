#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    
    vector<int> s;
    ll p = 1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] != 1) {
            s.push_back(i);
            p *= a[i];
            p = min(p, MOD);
        }
    }

    if(p == MOD) {
        cout << s[0] + 1 << " " << s[s.size() - 1] + 1 << '\n';
        return;
    }

    array<int,2> bounds = {0,0};
    ll best = 0;
    for(int i = 0; i < s.size(); i++) {
        ll curr = 1;
        ll currs = 0;
        for(int j = i; j < s.size(); j++) {
            curr *= a[s[j]];
            currs += a[s[j]] - 1;
            if(curr - currs - (s[j] - s[i] + 1) > best) {
                best = curr - currs - (s[j] - s[i] + 1);
                // cout << "from " << s[i] << " to " << s[j] << " diff : " << curr - currs - (s[j] - s[i] + 1) << '\n';
                // cout << "c : " << curr << " cs : " << currs << '\n';
                bounds = {s[i], s[j]};
            }
        }
    }

    cout << bounds[0] + 1 << " " << bounds[1] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}