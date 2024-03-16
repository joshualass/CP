#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll x; cin >> x;
    x -= 2;
    vector<pair<ll,int>> a;
    a.push_back({1,0});
    int i = 1;
    while(x) {
        ll cnt = 1;
        int j = 0;
        while(j < a.size()) {
            if(cnt + a[j].first > x) break;
            cnt += a[j].first;
            j++;
        }
        x -= cnt;
        a.insert(a.begin() + j,{cnt,i++});
    }
    vector<ll> ans(a.size());
    for(int i = 0; i < a.size(); i++) {
        ans[a[i].second] = i;
    }
    cout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}