//http://www.usaco.org/index.php?page=viewproblem2&cpid=496
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("cowjog.in","r",stdin);
    freopen("cowjog.out","w",stdout);
    
    ll n, t; cin >> n >> t;
    vector<pair<ll,ll>> v(n);
    for(int i = 0; i < n; i++) {
        ll p, s; cin >> p >> s;
        v[i] = {p,p+s*t};
    }
    sort(v.begin(),v.end());
    multiset<ll> s;
    for(int i = 0; i < n; i++) {
        if(s.size() && s.lower_bound(v[i].second) != s.begin()) {
            s.erase(--s.lower_bound(v[i].second));
        }
        s.insert(v[i].second);
    }
    cout << s.size() << "\n";
    return 0;
}