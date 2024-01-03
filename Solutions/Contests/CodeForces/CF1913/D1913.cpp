#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
struct MinTree {
    static constexpr T base = {1e9 + 1,1e9};
    T f(T a, T b) {
        return min(a,b); //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    MinTree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

ll dfs(int l, int r, int dir, MinTree<pair<ll,ll>> &tree) {
    if(l >= r) return 0;
    if(r - l == 1) return 1;
    int idx = tree.query(l,r).second;
    // cout << "l : " << l << " r : " << r << " idx : " << idx << '\n';
    ll left = dfs(l, idx, dir | 1, tree);
    ll right = dfs(idx + 1, r, dir | 2, tree);
    ll ans = (left + 1) * (right + 1);
    // cout << "left : " << left << " right : " << right << " ans : " << ans << '\n';
    if(dir & 1) {
        ans += left;
    }
    if(dir & 2) {
        ans += right;
    }
    // cout << "l : " << l << " r : " << r << " ans : " << ans << '\n';
    return ans % MOD;
}

void solve() {
    int n; cin >> n;
    MinTree<pair<ll,ll>> tree(n);
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        tree.update(i,{num,i});
    }
    cout << dfs(0,n,0,tree) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}