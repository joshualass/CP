#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(2);
    for(auto &x : a) cin >> x;
    int s = 0, d = 0;
    for(int i = 0; i < a[0].size(); i++) {
        if(a[0][i] == a[1][i]) {
            s++;
        } else {
            d++;
        }
    }

    cout << min(s,n) + min((int) a[0].size() - n, d) << '\n';

    return 0;
}