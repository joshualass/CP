#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    set<int> s;
    for(int i = 0; i < n * 2; i++) s.insert(i);

    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;

    int mx = *max_element(a.begin(), a.end());

    res += 1LL * mx * n;

    s.erase(mx);
    res += *s.begin();

    set<int> sa(a.begin(), a.end());

    for(int i = 1; i < n; i++) {
        if(sa.count(*s.begin())) {
            s.erase(s.begin());
        }
        res += *s.begin();
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}