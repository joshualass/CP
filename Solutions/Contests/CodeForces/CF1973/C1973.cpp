#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int idx = -1;
    vector<int> v(n);
    for(int i = 0 ; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
        if(num == 1) idx = i;
    }
    vector<pair<int,int>> mins;
    vector<pair<int,int>> maxs;

    for(int i = 0; i < n; i++) {
        if((i & 1) == (idx & 1)) {
            mins.push_back({v[i],i});
        } else {
            maxs.push_back({v[i],i});
        }
    }

    sort(maxs.begin(), maxs.end());
    sort(mins.begin(), mins.end());
    int lo = n, hi = n/2;
    vector<int> res(n);
    for(int i = 0; i < n / 2; i++) {
        res[maxs[i].second] = lo--;
        res[mins[i].second] = hi--;
    }
    for(int i = 0; i < n;i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}