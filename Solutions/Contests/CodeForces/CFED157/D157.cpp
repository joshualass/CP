#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> a(n-1);

    for(auto &x: a) cin >> x;

    int curr = 0;

    vector<int> transform(n);

    int highest = 0;

    for(int i = 0; i < n - 1; i++) {
        curr ^= a[i];
        transform[i+1] = curr;
        highest = max(highest,transform[i+1]);
    }

    int fix = highest - (n - 1);

    for(int i = 0; i < n; i++) {
        transform[i] ^= fix;
    }

    for(auto x : transform) cout << x << " ";

    cout << '\n';

    return 0;
}