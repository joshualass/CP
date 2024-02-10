#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    set<int> all;
    set<int> a, b;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num <= k) {
            a.insert(num);
            all.insert(num);
        }
    }
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        if(num <= k) {
            b.insert(num);
            all.insert(num);
        }
    }
    if(a.size() >= k / 2 && b.size() >= k / 2 && all.size() == k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}