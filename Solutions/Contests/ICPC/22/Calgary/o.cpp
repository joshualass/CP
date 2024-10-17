#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = k - 1; i < n; i += k) {
        cout << a[i] << " ";
    }

    return 0;
}