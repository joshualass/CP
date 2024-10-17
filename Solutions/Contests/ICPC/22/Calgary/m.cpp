#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int k = INT_MAX;

    for(int i = n / 2; i >= 1; i--) {
        int cnt = 1, ok = 1;
        for(int j = i * 2 - 1; j < n; j += i) {
            if(a[j] <= a[j-i]) {
                ok = 0;
            }
            cnt++;
        }
        if(cnt >= 2 && ok) {
            k = i;
        }
    }

    if(k == INT_MAX) {
        cout << "ABORT!\n";
    } else {
        cout << k << '\n';
    }

    return 0;
}