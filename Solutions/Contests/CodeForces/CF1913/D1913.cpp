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

template<typename T>
struct AddTree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    AddTree(int n = 0, T def = base) : s(n*2,def), n(n) {}
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

// pair<ll,ll> dfs(ll i, ll l, ll r, MinTree<pair<ll,ll>> &tree, AddTree<ll> &cnts) {
//     ll left = 1;
//     ll right = 1;
//     ll ans = 1;
//     //try to the left
//     if(i != l) {//can't go left anymore
//         pair<ll,ll> test_left = dfs(tree.query(l,i).second, l, i, tree, cnts);
//         left = cnts.query(l,test_left.second + 1) + 1;
//         left %= MOD;
//     }
//     if(i != r - 1) {//can't go right anymore
//         pair<ll,ll> test_right = dfs(tree.query(i + 1, r).second, i + 1, r, tree, cnts);
//         right = cnts.query(test_right.second,r) + 1;
//         right %= MOD;
//     }
//     ans *= left;
//     ans %= MOD;
//     ans *= right;
//     ans %= MOD;
//     cnts.update(i,ans);
//     cout << "i : " << i << " left : " << left << " right : " << right << " ans : " << ans << '\n';
//     // cout << "returning ans : " << ans << '\n';
//     return {ans,i};
// }

void dfs(ll i, ll l, ll r, MinTree<pair<ll,ll>> &tree, vector<ll> &cnts, vector<ll> &lefts, vector<ll> &rights) {
    ll left = 1;
    ll right = 1;
    if(i != l) {
        ll idx = tree.query(l,i).second;
        dfs(idx, l, i, tree, cnts, lefts, rights);
        left = cnts[idx] + lefts[idx];
        left %= MOD;
    }
    if(i != r - 1) {
        ll idx = tree.query(i + 1, r).second;
        dfs(idx, i + 1, r, tree, cnts, lefts, rights);
        right = cnts[idx] + rights[idx];
        right %= MOD;
    }
    lefts[i] = left;
    rights[i] = right;
    ll ans = (left * right) % MOD;
    cnts[i] = ans;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;

    vector<ll> v(n);
    MinTree<pair<ll,ll>> tree(n);
    vector<ll> cnts(n); //stores number of ways to make subarray including this element
    vector<ll> lefts(n); //stores number of ways to make left subarray
    vector<ll> rights(n); //stores number of ways to make right subarray
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = num;
        tree.update(i,{num,i});
    }
    ll start_idx = tree.query(0,n).second;
    dfs(start_idx, 0, n, tree, cnts, lefts, rights);
    cout << "cnts : " << cnts << '\n';
    cout << cnts[start_idx] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}