#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
We see that element m and m + 1 will be the same for even m. 
Therefore, parity stays consistent until then. 
Add until sequence is odd length. Then, every pair of elements we add will be the same. Use this to help us with a dfs. 
*/

void solve() {
    
    ll n, l, r; cin >> n >> l >> r;
    l--;

    vector<int> a(n);
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i) {
            p[i] = p[i-1] ^ a[i];
        } else {
            p[i] = a[i];
        }
    }

    auto add = [&]() -> void {
        a.push_back(p[(a.size() - 1) / 2]);
        p.push_back(p.back() ^ a.back());
    };

    if(n % 2 == 0) {
        add();
        n++;
    }

    vector<array<ll,2>> pc0 = {{1, 0}, {2, 0}};
    vector<array<ll,2>> pc1 = {{0, 1}, {0, 2}};
    if(p[n-1]) {
        for(int i = 0; i < 62; i++) {
            pc0.push_back({{pc0.back()[1], pc0.back()[0] * 2 + pc0.back()[1]}});
            pc1.push_back({{pc1.back()[1], pc1.back()[0] * 2 + pc1.back()[1]}});            
        }
    } else {
        for(int i = 0; i < 62; i++) {
            pc0.push_back({});
            pc1.push_back({0,2});
        }
    }

    ll res = 0;

    auto add_score = [&](int t, int d) -> ll {
        if(d == 0) {
            return t;
        } else {
            if(t) {
                return pc1[d][1];
            } else {
                return pc0[d][1];
            }
        }
    };


    auto dfs = [&](auto self, ll li, ll ri, int t, int depth) -> void {
        //no overlap
        if(ri <= l || li >= r) return; 
        //check if there is complete overlap
        if(li >= l && ri <= r) {
            ll add = add_score(t, depth);
            res += add;
            return;
        }
        ll m = (li + ri) / 2;
        if(depth == 1) {
            self(self, li, m, t, 0);
            self(self, m, ri, t, 0);
        } else {
            if(p[n-1]) {
                self(self, li, m, (t ? 0 : 1), depth - 1);
                self(self, m, ri, 1, depth - 1);
            } else {
                self(self, li, m, t, depth - 1);
                self(self, m, ri, 0, depth - 1); 
            }
        }
    };

    if(accumulate(a.begin(), a.end(), 0)) { //not all 0
        for(int i = 0; i < n; i++) {
            if(i >= l && i < r) res += a[i];
            if(i >= n / 2) {
                ll start = n, r_len = 2, len = n + 1, offset = (i - n / 2) * 2;
                int depth = 1;
                while(1) {
                    ll li = start + offset;
                    ll ri = li + r_len;
                    if(li >= r) break;
                    dfs(dfs, li, ri, p[i], depth++);
                    start += len;
                    r_len *= 2;
                    len *= 2;
                    offset *= 2;
                }
            }
        }

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}