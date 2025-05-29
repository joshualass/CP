#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll inf = 1e18;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node == query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != -1){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
    bool cond_range(T query_val, T cur) {
        return cur >= query_val;
    }
    int find_first_range(int l, int r, T query_val) {
        T cur = base;
        return _find_first_range(1, 0, size, l, r, query_val, cur);
    }
    int _find_first_range(int idx, int cl, int cr, int tl, int tr, T qv, T &cur) {
        if(cr <= tl || cl >= tr) return -1; //no overlap here, cya
        if(isLeaf(idx)) {
            if(cond_range(qv, cur)) return -1; //already done, do not add more
            cur = comb(cur, v[idx]);
            if(cond_range(qv, cur)) { //done now, this is the earliest
                return idx - size;
            } else { //not done, more work to do
                return -1;
            }
        }
        if(cl >= tl && cr <= tr) { //complete overlap, have this so that the complexity of this algorithm is truly logn
            if(!cond_range(qv, comb(cur, v[idx]))) { //still bad, do not go down
                cur = comb(cur, v[idx]);
                return -1;
            }
        }
        int mid = (cl + cr) / 2;
        int try_left = _find_first_range(idx * 2, cl, mid, tl, tr, qv, cur);
        if(try_left != -1) return try_left;
        return _find_first_range(idx * 2 + 1, mid, cr, tl, tr, qv, cur);
    }
};

/*
general find first logic
just like a query, make sure there is some overlap
then see if there is anything good in interval to keep pursuing
if so, see if done if leaf else, try the greedy sides. 
*/

//TODO check that range properly works with tl and tr. only tested for tl = 0 and tr = n. 

void solve() {

    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);

    for(int &x : a) {
        cin >> x;
        x--;
    }

    auto get_r = [&](int i) -> int {
        return (i - k + 1 + n) % n;
    };
    
    auto get_dist = [&](int l, int r) -> int {
        if(l > r) swap(l, r);
        return min(r - l, l + n - r);
    };

    // set<int> s;
    Tree<int> tree(n + 1, 1);
    // for(int i = 0; i <= n; i++) s.insert(i);

    vector<int> l(n), r(n); //if the current boundary is at this position, gets the next value to compute in the dp

    for(int i = 0; i < k; i++) {
        // s.erase(a[i]);
        tree.update(a[i], 0);
    }

    int start;

    for(int i = 0; i < n; i++) {
        // s.insert(a[(i-1+n)%n]);
        tree.update(a[(i-1+n)%n], 1);
        // s.erase(a[(i+k-1)%n]);
        tree.update(a[(i+k-1)%n], 0);
        // l[a[i]] = *s.upper_bound(a[i]);
        l[a[i]] = tree.find_first(a[i] + 1, n + 1, 1).first;
        // r[a[(i + k - 1) % n]] = *s.upper_bound(a[(i + k - 1) % n]);
        r[a[(i + k - 1) % n]] = tree.find_first(a[(i + k - 1) % n] + 1, n + 1, 1).first;
        if(i == 0) {
            // start = *s.begin();
            start = tree.find_first(0, n + 1, 1).first;
        }
        b[a[i]] = i;
    }

    // cout << "l : " << l << "\n";
    // cout << "r : " << r << '\n';

    vector<array<ll,2>> dp(n, {inf, inf});

    ll res = inf;

    auto transition = [&](int w, int nx, ll prev_val) -> void {
        if(nx == n) res = min(res, prev_val);
        else {
            dp[nx][0] = min(dp[nx][0], prev_val + get_dist(w, b[nx])); //left
            dp[nx][1] = min(dp[nx][1], prev_val + get_dist(w, get_r(b[nx])));
        }
    };

    transition(0, start, 0);

    for(int i = 0; i < n; i++) {
        int nxl = l[i], nxr = r[i];
        transition(b[i], nxl, dp[i][0]);
        transition(get_r(b[i]), nxr, dp[i][1]);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
