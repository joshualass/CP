#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int ncs, ne; cin >> ncs >> ne;
    vector<ll> a(ncs), b(ne);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    ld avg_cs = accumulate(a.begin(), a.end(), 0LL) / ((ld) ncs);
    ld avg_e = accumulate(b.begin(), b.end(), 0LL) / ((ld) ne);
    int res= 0;
    for(int x : a) if(x < avg_cs && x > avg_e) res++;
    cout << res << '\n';
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}