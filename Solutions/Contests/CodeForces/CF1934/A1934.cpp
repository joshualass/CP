#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int ans = 0;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    sort(v.begin(),v.end());
    int ai = v[0], aj = v[n-1], ak = v[1], al = v[n-2];
    cout << abs(ai - aj) + abs(aj - ak) + abs(ak - al) + abs(al-ai) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}