#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int N = 1e6;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

void solve() {
    
    int n, m, q; cin >> n >> m >> q;
    
    // set<array<int,2>> s;
    pb_set<ll> s;

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        if(u > v) swap(u, v);
        s.insert({1LL * u * n + v});
        // s.insert({u, v});
        // s.insert({v, u});
    }

    vector<array<int,2>> qs;

    int u = 0, v = 0;

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;

        int curu = (u + a) % n, curv = (v + b) % n;
        
        if(curu > curv) swap(curu, curv);

        if(s.find(1LL * curu * n + curv) != s.end()) {
            qs.push_back({curu, curv});
            s.erase(1LL * curu * n + curv);
        } else {
            qs.push_back({-1,-1});
        }

        u = (u * 2 + 1) % n;
        v = (v * 3 + 1) % n;
    }

    dsubuild(n);

    int comps = n, first = q;

    for(auto info : s) {
        int u = info / n, v = info % n;
        if(find(u) != find(v)) {
            merge(u, v);
            comps--;
        }
    }

    for(int i = q - 1; i >= 0 && comps > 1; i--) {
        if(qs[i] != array<int,2>{-1,-1}) {
            auto [u, v] = qs[i];
            if(find(u) != find(v)) {
                merge(u, v);
                comps--;
            }
        }
        first = i;
    }

    for(int i = 0; i < q; i++) {
        cout << (i < first) << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}