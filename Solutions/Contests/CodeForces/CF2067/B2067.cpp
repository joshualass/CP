#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    map<int,vector<int>> m;
    set<int> s;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        m[a[i]].push_back(i);
        s.insert(i+1);
    }
    s.insert(n+1);
    int lo = n;
    m.erase(0);
    for(int i = n - 1; i >= 0; i--) {
        s.erase(a[i]);
        while(m.size() && (m.begin())->first < *s.begin()) {
            int t = (m.begin())->first;
            int tt = *min_element(m[t].begin(),m[t].end());
            if(tt < i) {
                lo = min(lo,tt);
            }
            m.erase(t);
        }
    }
    int f = 0;
    for(int i = 0; i < lo; i++) {
        if(a[i] == 0) f = 1;
    }
    cout << n - count(a.begin(),a.end(),0) + f << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}