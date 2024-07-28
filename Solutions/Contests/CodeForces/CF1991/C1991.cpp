#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> ops;
    for(int op = 0; op < 40; op++) {
        int highest = *max_element(a.begin(), a.end());
        int x = (highest + 1) / 2;
        ops.push_back(x);
        for(int i = 0; i < n; i++) {
            a[i] = abs(a[i] - (x));
        }
        // if(count(a.begin(), a.end(),0) == n) break;
    }

    if(count(a.begin(), a.end(),0) == n) {
        cout << ops.size() << '\n';
        for(int i = 0; i < ops.size(); i++) {
            cout << ops[i] << " \n"[i == ops.size() - 1];
        }
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}