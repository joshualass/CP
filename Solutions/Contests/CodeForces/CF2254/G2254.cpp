#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

struct Tree {
    typedef ll T;
    static constexpr T base = {};
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    Tree(int n, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    Tree(vector<T> a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        assert(n == sz(a));
        for(int i = 0; i < n; i++) {
            v[i + size] = a[i];
        }
        for(int i = size - 1; i >= 1; i--) {
            v[i] = f(v[i * 2], v[i * 2 + 1]);
        }
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
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
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

const int N = 2e5;
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


void solve() {
    
    int n; cin >> n;
    vector<array<int,2>> a(n);
    ll cur = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        cur += a[i][0];
        a[i][1] = i;
    }

    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        ch[p-1].push_back(i);
    }

    vector<int> tin(n), tout(n);

    int time = 0;
    Tree tree(n);

    auto dfs = [&](auto self, int i) -> void {
        tin[i] = time++;
        tree.update(time, i);
        for(int c : ch[i]) {
            self(self, c);
        }
        tout[i] = time;
    };

    dfs(dfs, 0);
    dsubuild(n);

    sort(a.begin(), a.end());

    vector<ll> res(n, -1);
    int p = 0;
    for(int i = n - 1; i >= 0; i--) {
        res[i] = cur;
        int f = 0;
        while(p < n) {
            auto [val, idx] = a[n - 1 - i];
            int l = tin[idx], r = tout[idx];
            int q = tree.query(l + 1, r);
            if(q) {
                
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}