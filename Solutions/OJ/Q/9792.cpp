#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

struct Tree {
    typedef int T;
    static constexpr T unit = 0;
    T f(T a, T b) { return a + b;}
    vector<T> s; int n;
    Tree(int n = 0, T def = unit):s(n * 2, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for(b += n, e += n; b < e; b /= 2, e /= 2) {
            if(b % 2) ra = f(ra, s[b++]);
            if(e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    set<array<int,2>> s;

    vector<array<int,2>> ops;
    int nx = n;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] != nx) {
            // ops.push_back({1 + i + ((int) ops.size()), 1});
            s.insert({-a[i], i});
        } else {
            nx--;
        }
    }

    Tree tree(n);
    for(auto op : s) {
        ops.push_back({op[1] + 1 + tree.query(op[1], n), 1});
        tree.update(op[1], 1);
    }

    cout << ops.size() << " " << ops.size() << '\n';
    for(auto op : ops) {
        cout << op[0] << " " << op[1] << '\n';
    }

    return 0;
}