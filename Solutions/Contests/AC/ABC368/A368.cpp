#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int k; cin >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int i = 0; i < n; i++) {
        cout << a[(i + n - k) % n] << " \n"[i == n - 1];
    }


    return 0;
}