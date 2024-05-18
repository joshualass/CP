#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[num-1]++;
    }   
    cout << count(v.begin(), v.end(), 2) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}