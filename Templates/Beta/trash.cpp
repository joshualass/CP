#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll det(array<ll,2> a, array<ll,2> b) {
    return a[0] * b[1] - a[1] * b[0];
}

ll calc_area(array<ll,2> a, array<ll,2> b, array<ll,2> c) {
    return abs(det(a, b) + det(b, c) + det(c, a));  
}

ll solve_slow(int n, vector<int> a) {

    ll res = LLONG_MAX;

    auto dfs = [&](auto self, vector<int> y) {
        if(sz(y) == n) {
            if(count(y.begin(), y.end(), 0) && count(y.begin(), y.end(), 1) && count(y.begin(), y.end(), 2)) {
                ll lo = 0;
                for(int i = 0; i < n; i++) {
                    for(int j = i + 1; j < n; j++) {
                        for(int k = j + 1; k < n; k++) {
                            if(y[i] != y[j] && y[i] != y[k] && y[j] != y[k]) {
                                lo = max(lo, calc_area({a[i], y[i]}, {a[j], y[j]}, {a[k], y[k]}));
                            }
                        }
                    }
                }
                // if(lo == 39) {
                //     cout << "y : " << y << endl;
                // }
                res = min(res, lo);
            }
            return;
        }
        for(int i = 0; i < 3; i++) {
            y.push_back(i);
            self(self, y);
            y.pop_back();
        }
    };

    dfs(dfs, {});

    return res;

}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    
    ll res = LLONG_MAX;
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 2; j < n; j++) {
            ll cur = 0;
            {
                array<ll,2> x = {a[0], 0};
                array<ll,2> y = {a[j-1], 1};
                array<ll,2> z = {a[j], 2};
                cur = max(cur, calc_area(x, y, z));
            }
            {
                array<ll,2> x = {a[i], 0};
                array<ll,2> y = {a[i+1],1};
                array<ll,2> z = {a[n - 1], 2};
                cur = max(cur, calc_area(x, y, z));
            }
            // cout << "i : " << i << " j : " << j << " cur : " << cur << endl;
            res = min(res, cur);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            ll cur0 = 0, cur1 = 0;
            array<ll,2> x0 = {a[i], 2};
            array<ll,2> y0 = {a[j], 1};
            array<ll,2> x1 = {a[i], 1};
            array<ll,2> y1 = {a[j], 2};
            for(int k = 0; k < n; k++) {
                if(k != i && k != j) {
                    array<ll,2> z = {a[k], 0};
                    cur0 = max(cur0, calc_area(x0, y0, z));
                    cur1 = max(cur1, calc_area(x1, y1, z));
                    break;
                }
            }
            for(int k = n - 1; k >= 0; k--) {
                if(k != i && k != j) {
                    array<ll,2> z = {a[k], 0};
                    cur0 = max(cur0, calc_area(x0, y0, z));
                    cur1 = max(cur1, calc_area(x1, y1, z));
                    break;
                }
            }
            res = min({res, cur0, cur1});
        }
    }

    for(int i = 0; i < n; i++) {
        for()
    }
        
    cout << res << '\n';    
    
    // cout << "res slow : " << solve_slow(n, a) << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}