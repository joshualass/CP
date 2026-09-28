#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 2; i < n; i++) {
        if(a[i-2] == a[i-1] && a[i-1] == a[i]) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}