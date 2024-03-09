#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int lo = INT_MIN;
    int hi = INT_MAX;
    vector<int> equals;
    for(int i = 0; i < n; i++) {
        int type; cin >> type;
        int num; cin >> num;
        if(type == 1) {
            lo = max(lo, num);
        }
        if(type == 2) {
            hi = min(hi, num);
        }
        if(type == 3) {
            equals.push_back(num);
        }
    }
    int cnt = hi - lo + 1;
    for(int i : equals) {
        if(i >= lo && i <= hi) cnt--;
    }
    cout << max(cnt,0) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}