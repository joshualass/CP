#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) {
        cin >> x;
        x--;
    }

    vector<int> res(n);
    for(int i = 0; i < n; i++) {
        res[b[i]] = b[a[i]];
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}
