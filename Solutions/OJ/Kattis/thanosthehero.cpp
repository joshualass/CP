#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    ll res = 0;
    for(int i = n - 1; i > 0; i--) {
        if(v[i-1] >= v[i]) {
            res += v[i-1] - v[i] + 1;
            v[i-1] = v[i] - 1;
        }
    }
    if(*min_element(v.begin(),v.end()) < 0) {
        cout << "1\n";
    } else {
        cout << res << '\n';
    }
    return 0;
}