#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    map<ll,ll> m;
    vector<pair<ll,int>> v(n);

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = {num,i};
        m[num] += num;
    }

    sort(v.rbegin(), v.rend());

    vector<ll> ans(n);
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        while(m.upper_bound(v[i].first) != m.end()) {
            sum += (*m.upper_bound(v[i].first)).second;
            m.erase(m.upper_bound(v[i].first)->first);
        }
        ans[v[i].second] = sum;
    }

    for(auto a : ans) cout << a << " ";
    cout << '\n';

    return 0;
}