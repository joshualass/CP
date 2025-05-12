#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    int p = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(abs(a[i]) != 1) p = i;
    }

    set<int> s;

    auto get_max = [&](vector<int> b) -> int {
        int res = 0;
        int c = 0;
        for(int x : b) {
            c += x;
            c = max(c, 0);
            res = max(res, c);
        }
        return res;
    };

    auto add_pos = [&](vector<int> b) -> void {
        int hi = get_max(b);
        for(int &x : b) x *= -1;
        int lo = -get_max(b);
        for(int i = lo; i <= hi; i++) s.insert(i);
    };

    add_pos(vector<int>(a.begin(), a.begin() + p));
    add_pos(vector<int>(a.begin() + p + 1, a.end()));

    int lol = 0, lor = 0, hil = 0, hir = 0;
    int c = 0;
    for(int i = p - 1; i >= 0; i--) {
        c += a[i];
        lol = min(lol, c);
        hil = max(hil, c);
    }
    c = 0;
    for(int i = p + 1; i < n; i++) {
        c += a[i];
        lor = min(lor, c);
        hir = max(hir, c);
    }

    for(int i = lol + lor; i <= hil + hir; i++) {
        s.insert(a[p] + i);
    }

    cout << s.size() << '\n';
    for(int x : s) cout << x << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}