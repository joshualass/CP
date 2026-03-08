#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        return max(a,b);
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
        // cout << "l : " << l << " r : " << r << endl;
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(m);
    for(int &x : a) cin >> x;
    sparse<int> sparse(a);
    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int xs, ys, xf, yf, k; cin >> xs >> ys >> xf >> yf >> k;
        ys--; yf--;
        if(abs(xs - xf) % k || abs(ys - yf) % k) {
            cout << "NO\n";
            continue;
        }
        if(ys > yf) {
            swap(xs, xf);
            swap(ys, yf);
        }
        if(ys == yf) {
            cout << "YES\n";
            continue;
        }
        // cout << "ys : " << ys << " yf : " << yf << endl;
        int mx = sparse.query(ys, yf);
        int rem = n - xs;
        rem = rem / k * k;
        int tmax = xs + rem;
        cout << (tmax > mx ? "YES" : "NO") << '\n';
    }

    return 0;
}
