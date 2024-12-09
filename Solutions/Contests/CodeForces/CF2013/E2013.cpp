#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);

    for(int &x : a) cin >> x;

    int highest = *max_element(a.begin(), a.end());

    ll sum = 0;
    int g = 0;

    int manual = min(n, 32 - __builtin_clz(highest));

    for(int i = 0; i < manual; i++) {
        int ming = gcd(g,a[0]);
        int minidx = 0;
  
        for(int j = 0; j < a.size(); j++) {
            if(gcd(g, a[j]) < ming) {
                ming = gcd(g,a[j]);
                minidx = j;
            }
        }

        g = ming;
        sum += g;
        a.erase(a.begin() + minidx, a.begin() + minidx + 1);

    }

    sum += 1LL * (n - manual) * g;

    cout << sum << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}