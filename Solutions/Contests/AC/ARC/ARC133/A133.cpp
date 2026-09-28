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

    for(auto &x: v) cin >> x;

    int remove = v[0];

    for(int i = 1; i < n; i++) {
        if(v[i] > v[i-1]) {
            remove = v[i];
        } else if(v[i] < v[i-1]) {
            break;
        }
    }

    for(auto &x: v) {
        if(x != remove) cout << x << " ";
    }

    cout << endl;
    return 0;
}