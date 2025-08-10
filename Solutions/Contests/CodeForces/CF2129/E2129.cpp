#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
impl thoughts

long lol?
*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

struct ds {
    vector<int> cnts, vals, bucket_counts, in;
    int sz, SQN;
    ds(int n) {
        sz = 1 << (32 - __builtin_clz(n));
        SQN = sqrt(sz);
        while(SQN * SQN < sz) SQN++;
        cnts.assign(sz, 0), vals.assign(sz, 0), bucket_counts.assign(SQN, 0), in.assign(sz, 0);
    }

    void add(int idx) {
        assert(in[idx] == 0);
        assert(idx < sz);
        in[idx] = 1;
        cnts[vals[idx]]++;
        bucket_counts[vals[idx] / SQN]++;
    }

    void erase(int idx) {
        assert(in[idx]);
        assert(idx < sz);
        in[idx] = 0;
        cnts[vals[idx]]--;
        bucket_counts[vals[idx] / SQN]--;
    }

    void update(int idx, int x) {
        assert(idx < sz);
        if(in[idx]) {
            erase(idx);
            vals[idx] ^= x;
            add(idx);
        } else {
            vals[idx] ^= x;
        }
    }

    int query(int k) {
        assert(accumulate(bucket_counts.begin(), bucket_counts.end(), 0) >= k);
        int sum = 0;
        for(int i = 0; i < SQN; i++) {
            if(sum + bucket_counts[i] >= k) {
                for(int j = i * SQN; j < (i + 1) * SQN; j++) {
                    sum += cnts[j];
                    if(sum >= k) return j;
                }
                assert(0);
            }
            sum += bucket_counts[i];
        }
        assert(0);
    }

    void print() {
        cout << "ds n : " << sz << " sqn : " << SQN << '\n';
        cout << "cnts : " << cnts << "\n";
        cout << "vals : " << vals << "\n";
        cout << "bucket_counts : " << bucket_counts << "\n";
        cout << "in : " << in << "\n";
    }
};

void solve() {
    
    int n, m; cin >> n >> m;
    n++;
    // int n = 150001, m = 0;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int l = 0, r = 0;
    ds z(n);

    auto add = [&](int right) -> void {
        if(right) {
            for(int x : adj[r]) {
                if(x >= l && x < r) {
                    z.update(x, r);
                    z.update(r, x);
                }
            }
            z.add(r);
            r++;
        } else {
            for(int x : adj[l-1]) {
                if(x >= l && x < r) {
                    z.update(l - 1, x);
                    z.update(x, l - 1);
                }
            }
            z.add(l - 1);
            l--;
        }
    };

    auto erase = [&](int right) -> void {
        if(right) {
            for(int x : adj[r-1]) {
                if(x >= l && x < r) {
                    z.update(x, r - 1);
                    z.update(r - 1, x);
                }
            }
            z.erase(r - 1);
            r--;
        } else {
            for(int x : adj[l]) {
                if(x >= l && x < r) {
                    z.update(l, x);
                    z.update(x, l);
                }
            }
            z.erase(l);
            l++;
        }
    };

    map<int,int> buckets;
    int SQM = sqrt(m * 2);
    int cur = adj[0].size();
    int SQN = sqrt(n);
    while(SQN * SQN < n) SQN++;

    // cout << "SQM : " << SQM << " cur : " << cur << '\n';

    for(int i = 1; i < n; i++) {
        if(cur + adj[i].size() > SQM || (buckets.size() ? (--buckets.end())->first : 0) + SQN <= i) {
            int sz = buckets.size();
            buckets[i] = sz;
            cur = 0;
        }
        cur += adj[i].size();
    }

    int sz = buckets.size();
    buckets[n] = sz;

    int bs = buckets.size();

    vector<vector<vector<array<int,4>>>> queries(bs, vector<vector<array<int,4>>>(bs));


    // cout << "buckets : " << buckets << '\n';

    int q; cin >> q;
    // int q = 150000;
    for(int qq = 0; qq < q; qq++) {
        int l, r, k; cin >> l >> r >> k;
        r++;
        // int l = rng() % n + 1, r = rng() % n + 1;
        // if(l > r) swap(l, r);
        // r++;
        // int k = rng() % (r - l) + 1;
        int lb = (buckets.upper_bound(l))->second;
        int rb = (buckets.lower_bound(r))->second;
        queries[lb][rb].push_back({l, r, k, qq});
        // queries[0][0].push_back({l, r, k, qq});
    }

    vector<int> res(q, -1);
    for(int i = 0; i < bs; i++) {
        for(int j = (i & 1 ? bs - 1 : 0); (i & 1 ? j >= 0 : j < bs); (i & 1 ? j--: j++)) {
            for(auto [ql, qr, k, id] : queries[i][j]) {
                while(ql < l) add(0);
                while(r < qr) add(1);
                while(l < ql) erase(0);
                while(r > qr) erase(1);
                // cout << "ql : " << ql << " qr : " << qr << " l : " << l << " r : " << r << " k : " << k << " id : " << id << '\n';
                // z.print();
                assert(l == ql && r == qr);
                res[id] = z.query(k);
            }
        }
    }

    assert(count(res.begin(), res.end(), -1) == 0);

    for(int x : res) cout << x << "\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // solve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}