#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        m[num]++;
    }
    int res = 0, cnt = 0, lo = 0;
    for(map<int,int>::iterator it = m.begin(); it != m.end(); it++) {

        int v = it->first;
        if(lo < v) {
            cnt = 0;
            lo = v;
        }

        while(lo < v + k && m.count(lo)) {
            cnt += m[lo++];
        }
        res = max(res, cnt);
        cnt -= it->second;
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