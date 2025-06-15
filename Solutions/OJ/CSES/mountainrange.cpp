#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        if(a[0] == b[0]) {
            if(a[1] < b[1]) {
                return a;
            } else {
                return b;
            }
        }
        if(a[0] > b[0]) {
            return a;
        } else {
            return b;
        }
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
    //[l, r]
    T iquery(int l, int r) {
        if(l > r) return {-1,-1};
        return query(l, r + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    int hi = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
        hi = max(hi, x);
    }

    sparse<array<ll,2>> s(a);
    int res = 0;

    auto dfs = [&](auto self, int l, int r) -> int {
        if(l > r) return 0;

        vector<int> pts;
        pts.push_back(l - 1);
        int mx = s.iquery(l, r)[0];
        int cl = l;
        while(s.iquery(cl, r)[0] == mx) {
            int idx = s.iquery(cl, r)[1];
            pts.push_back(idx);
            cl = idx + 1;
        }
        pts.push_back(r + 1);

        int res = 0;

        for(int i = 1; i < pts.size(); i++) {
            int lhs = pts[i-1], rhs = pts[i];
            res = max(res, self(self, lhs + 1, rhs - 1));
        }

        return res + 1;

    };

    cout << dfs(dfs, 0, n - 1) << '\n';


    return 0;
}
