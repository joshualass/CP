#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n - m + 1);
    for(ll &x : a) cin >> x;
    vector<ll> deltas(n);
    for(int i = 0; i < n - m; i++) {
        deltas[i + m] = a[i+1] - a[i];
    }

    for(int i = m; i < n; i++) deltas[i] += deltas[i - m];

    // cout << deltas << '\n';

    int q; cin >> q;

    vector<array<int,2>> queries(q);
    vector<array<int,3>> mo;
    vector<ll> mo_results(q, LLONG_MAX);

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        queries[i] = {l, r};
        if(r - l >= m) mo.push_back({l, r, i});
    }

    int bs = sqrt(n);

    sort(mo.begin(), mo.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        if(lhs[0] / bs != rhs[0] / bs) return lhs[0] < rhs[0];
        if(lhs[0] / bs % 2 == 0) {
            return lhs[1] / bs < rhs[1] / bs;
        } else {
            return lhs[1] / bs > rhs[1] / bs;
        }
    });

    vector<sparse<ll>> sparses(m);
    for(int i = 0; i < m; i++) {
        vector<ll> b;
        for(int j = i; j < n; j += m) b.push_back(deltas[j]);
        // cout << "i : " << i << " b : " << b << endl;
        sparses[i] = sparse<ll>(b);
    }

    int curl = 0, curr = 0;
    ll sum = 0;
    vector<ll> vals(m);

    auto update_group = [&](int i) -> void {
        sum -= vals[i];
        int l = (curl - i + m - 1) / m;
        int r = (curr - i + m - 1) / m;
        // cout << "i : " << i << " curl : " << curl << " curr : " << curr << endl;
        // cout << " l : " << l << " r : " << r << " true l : " << true_l << " true_r : " << true_r << endl;
        if(r > l) {
            vals[i] = sparses[i].query(l, r);
        } else {
            vals[i] = 0;
        }
        sum += vals[i];
    };

    for(auto [l, r, qidx] : mo) {
        // cout << "l : " << l << " r : " << r << " qidx : " << qidx << endl;
        while(curl > l) {
            curl--;
            update_group(curl % m);
        }
        while(curr < r) {
            curr++;
            update_group((curr - 1) % m);
        }
        while(curl < l) {
            curl++;
            update_group((curl - 1) % m);
        }
        while(curr > r) {
            curr--;
            update_group(curr % m);
        }
        mo_results[qidx] = sum;
    }

    for(int qq = 0; qq < q; qq++) {
        // cout << "qq : " << qq << endl;
        if(mo_results[qq] == LLONG_MAX) {
            cout << "unbounded\n";
        } else {
            ll val = a[0] + mo_results[qq];
            // cout << "a[0] : " << a[0] << " mo value : " << mo_results[qq] << endl;
            if(val >= 0) {
                val = (val + m - 1) / m;
            } else {
                val /= m;
            }

            cout << val << '\n';
        }
    }

    return 0;
}
