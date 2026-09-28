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
    for(int i = 0; i < n - 1; i++) {
        cout << v[i] * v[i+1] << " \n"[i == n - 2];
    }

    return 0;
}