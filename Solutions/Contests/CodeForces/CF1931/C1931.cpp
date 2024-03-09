#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    set<int> s(v.begin(), v.end());
    if(s.size() == 1) {
        cout << "0\n";
    } else {
        int lo = 1;
        while(v[lo-1] == v[lo]) lo++;
        int hi = n - 2;
        while(v[hi+1] == v[hi]) hi--;
        int frontsame = lo;
        int backsame = n - hi - 1;
        if(v.front() == v.back()) {
            cout << n - frontsame - backsame << '\n';
        } else {
            cout << n - max(frontsame, backsame) << '\n';
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