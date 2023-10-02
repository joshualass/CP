//https://codeforces.com/contest/772/problem/A
//straightforward binary search problem
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld n, p; cin >> n >> p;
    ld output = 0;
    vector<pair<ld,ld>> bat(n);
    for(int i = 0; i < n; i++) {
        ld a, b; cin >> a >> b;
        output += a;
        bat[i] = {a,b};
    }
    if(p >= output) {
        cout << "-1\n";
        return 0;
    }
    ld l = 0, r = 1e18;
    while(l + 1e-6 < r) {
        ld m = (l + r) / 2;
        ld powerallocated = m * p;
        for(int i = 0; i < n; i++) {
            ld powerneeded = bat[i].first * m - bat[i].second;
            powerallocated -= max((ld)0,powerneeded);
        }
        if(powerallocated < 0) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(10) << l << "\n";
    return 0;
}