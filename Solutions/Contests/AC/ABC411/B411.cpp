#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    n--;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int l = 0; l < n; l++) {
        for(int r = l + 1; r <= n; r++) {
            int sum = 0;
            for(int i = l; i < r; i++) sum += a[i];
            cout << sum << " \n"[r == n];
        }
    }

    return 0;
}
