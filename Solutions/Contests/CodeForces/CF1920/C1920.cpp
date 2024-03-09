#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool solve1(vector<int> &v, int size) {
    int g = -1;
    int n = v.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < n / size - 1; j++) {
            if(g == -1) {
                g = abs(v[i + j * size] - v[i + (j + 1) * size]);
            } else {
                g = gcd(g, abs(v[i + j * size] - v[i + (j + 1) * size]));
            }
        }
    }
    return g != 1;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    int cnt = 0;
    for(int part = 1; part <= n; part++) {
        if(n % part == 0 && solve1(v,part)) cnt++;
    }
    cout << cnt << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}