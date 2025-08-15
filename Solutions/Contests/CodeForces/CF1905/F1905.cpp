#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



void solve() {
    
    int n; cin >> n;
    vector<int> a(n), ra(n);
    set<int> after, before;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        ra[x] = i;
        after.insert(i);
    }

    if(is_sorted(a.begin(), a.end())) {
        cout << n - 2 << '\n';
        return;
    }

    before.insert(-1);
    after.insert(n);

    map<array<int,2>, int> m;
    int res = 0;
    
    for(int i = 0; i < n; i++) {
        after.erase(a[i]);
        if(a[i] == i) {
            if(*after.begin() == i + 1) {
                res++;
            } else {
                if(*++after.begin() >= i + 1) {
                    int before_val = *--before.end();
                    int after_val = *after.begin();
                    int before_idx = ra[before_val];
                    int after_idx = ra[after_val];
                    m[{before_idx, after_idx}]++;
                }
            }
        } else {
            int i_idx = ra[i];
            if(i_idx < i) {
                if(*after.begin() == i + 1) {
                    m[{i_idx, i}]++;
                }
            } else {
                if(*--before.end() == i - 1) {
                    m[{i, i_idx}]++;
                }
            }
        }
        before.insert(a[i]);
    }

    int mx = 0;
    for(auto [k, v] : m) mx = max(mx, v);

    cout << res + mx << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}