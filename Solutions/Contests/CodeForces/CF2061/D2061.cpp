#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    multiset<int> a, b;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a.insert(x);
    }

    auto insert_b = [&](int x) -> void {
        if(a.find(x) != a.end()) {
            a.erase(a.find(x));
        } else {
            b.insert(x);
        }
    };

    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        insert_b(x);
    }

    while(b.size() < a.size() && b.size()) {
        int last = *--b.end();
        b.erase(b.find(last));
        insert_b(last / 2);
        insert_b((last + 1) / 2);
    }

    cout << (a.empty() && b.empty() ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}