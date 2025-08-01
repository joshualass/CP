#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, multiset<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;    
    }

    set<int> uv;
    for(int i = 0; i < n; i++) {
        uv.insert(i);
    }
    vector<array<int,3>> res;

    for(int d = k; d <= min(n, k + 21); d++) {
        multiset<int> mn, mx;

        auto balance = [&]() -> void {
            while(mn.size() > mx.size()) {
                int val = *--mn.end();
                mn.erase(mn.find(val));
                mx.insert(val);
            }
            while(mx.size() > mn.size()) {
                int val = *mx.begin();
                mx.erase(mx.find(val));
                mn.insert(val);
            }
            while(mn.size() && mx.size() && *--mn.end() > *mx.begin()) {
                int lomv = *--mn.end(), himv = *mx.begin();
                mn.erase(mn.find(lomv));
                mx.erase(mx.find(himv));
                mn.insert(himv);
                mx.insert(lomv);
            }
        };

        for(int i = 0; i + 1 < d; i++) {
            mn.insert(a[i]);
        }
        for(int i = d - 1; i < n; i++) {
            mn.insert(a[i]);
            balance();
            // cout << "d : " << d << " i : " << i << " mn : " << mn << " mx : " << mx << '\n';
            if(d & 1) {
                int val = *--mn.end();
                if(uv.count(val)) {
                    uv.erase(val);
                    res.push_back({val, i - d + 1, i});
                }
            } else {
                int lo = *--mn.end(), hi = *mx.begin();
                while(uv.lower_bound(lo) != uv.end() && *uv.lower_bound(lo) <= hi) {
                    int val = *uv.lower_bound(lo);
                    uv.erase(val);
                    res.push_back({val, i - d + 1, i});
                }
            }
            int erase = a[i - d + 1];
            if(mn.count(erase)) {
                mn.erase(mn.find(erase));
            } else {
                mx.erase(mx.find(erase));
            }
        }
    }

    cout << res.size() << '\n';

    for(auto [v, l, r] : res) {
        cout << v + 1 << " " << l + 1 << " " << r + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}