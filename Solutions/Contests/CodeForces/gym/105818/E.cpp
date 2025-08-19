#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        return min(a,b);
    }
    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));
        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }
    }
    //[l,r) always. 
    T query(int l, int r) {
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, l; cin >> n >> l;
    vector<ll> et(n);
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        et[i] = 1 + l / x + i;
    }

    // cout << "et : " << et << '\n';
    sparse<ll> st(et);

    ll res = 0;
    for(int i = 0; i < n; i++) {
        int l = i, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            int ok = 1;
            if(st.query(i, m + 1) <= 1 + m) {
                r = m - 1;
            } else {
                l = m;
            }
        }
        int len = (l - i + 1);
        int left = n - (len + i);
        ll delta = 1LL * len * (len + 1) / 2 + 1LL * len * left;
        res += delta;
    }

    cout << res << '\n';

    return 0;
}
