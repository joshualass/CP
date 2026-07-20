#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

struct Tree {
    typedef array<int,2> T;
    static constexpr T base = {};
    array<int,30> cnts = {};
    vector<T> v;
    int n, size;
    // T f(T a, T b) { //change this when doing maximum vs minimum etc.
    //     return a + b;
    // }
    void change(int bit, int l, int r, int d) {
        if(v[l][1] > v[r][0]) cnts[bit] += d;
    }
    Tree(int n, T def = base) {
        assert(__builtin_popcount(n) == 1);
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        array<int,2> c = val;
        int bit = 0;
        while(curr != 1) {
            int l, r;
            if(curr & 1) { //handles non-communative operations
                l = curr ^ 1;
                // v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                l = curr;
                // v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            r = l ^ 1;
            change(bit, l, r, -1);
            v[curr] = c;
            change(bit, l, r, 1);
            c = {min(v[l][0], v[r][0]), max(v[l][1], v[r][1])};
            curr /= 2;
            bit++;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    int query() {
        for(int i = 29; i >= 0; i--) {
            if(cnts[i]) return 1 << i;
        }
        return 0;
    }
};

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    while(__builtin_popcount(n) != 1) {
        n++;
        a.push_back(1e9);
    }

    Tree tree(n);

    for(int i = 0; i < n; i++) {
        tree.update(i, {a[i], a[i]});
    }

    // cout << "tree cnts start : " << tree.cnts << endl;
    cout << tree.query() << '\n';


    for(int qq = 0; qq < q; qq++) {
        int i, x; cin >> i >> x;
        // i--;
        tree.update(i, {x, x});
        // cout << "qq : " << qq << " cnts : " << tree.cnts << endl;
        cout << tree.query() << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}