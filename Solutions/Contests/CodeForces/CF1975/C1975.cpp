#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int best = 0;
    for(int l = 2; l <= 10; l++) {
        for(int i = 0; i + l <= n; i++) {
            vector<int> v;
            for(int j = 0; j < l; j++) {
                v.push_back(a[i+j]);
            }
            sort(v.begin(), v.end());
            best = max(best, v[(v.size()+1)/2-1]);
        }
    }
    cout << best << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}