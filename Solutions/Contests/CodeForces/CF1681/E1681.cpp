#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
an unfortunately long implementation 

be more focused during implementation + draw things out to help out + maybe do math on paper to impl faster in the future?

*/

const ll inf = 1e18;

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

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<ll>> base = {{0,inf},{inf,0}};
struct Tree {
    typedef vector<vector<ll>> T;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        T res(2, vector<ll>(2, inf));
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return res;
    }
    Tree(int n, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    Tree(int n, vector<T> a) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, base);
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n - 1);
    vector<vector<vector<ll>>> b;
    for(int i = 0; i < n - 1; i++) {
        int _; cin >> _ >> a[i][0] >> a[i][1] >> _;
        vector<vector<ll>> nx;
        if(i) {
            b.push_back({
                {
                    1 + abs(a[i][0] - a[i-1][0]),
                    1 + (i + 1 - a[i-1][0]) + (i + 1 - a[i][1])
                },
                {
                    1 + (i + 1 - a[i-1][1]) + (i + 1 - a[i][0]),
                    1 + abs(a[i][1] - a[i-1][1])
                }
            });
        }
    }

    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;

    Tree tree(n - 2, b);
    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if(max(x1,y1) > max(x2,y2)) {
            swap(x1, x2);
            swap(y1, y2);
        }
        
        // cout << "x1 : " << x1 << " y1 : " << y1 << " x2 : " << x2 << " y2 : " << y2 << endl;

        int lo = max(x1, y1), hi = max(x2, y2);

        // cout << "lo : " << lo << " hi : " << hi << endl;
        
        if(lo == hi) {
            cout << abs(x1-x2) + abs(y1-y2) << '\n';
        } else {
            auto mat = tree.query(lo - 1, hi - 2);
            // cout << "mat" << endl;
            // for(auto x : mat) cout << x << endl;

            // cout << "lo : " << lo << " hi : " << hi << endl;

            ll res = inf;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    ll cost = 0;

                    if(i == 0) {
                        cost += 1 + abs(lo - x1) + abs(a[lo - 1][0] - y1);
                    } else {
                        cost += 1 + abs(lo - y1) + abs(a[lo - 1][1] - x1);
                    }

                    // cout << "im cost : " << cost << endl;

                    if(j == 0) {
                        cost += abs(hi - x2) + abs(y2 - a[hi-2][0]);
                    } else {
                        cost += abs(hi - y2) + abs(x2 - a[hi-2][1]);
                    }

                    // cout << "i : " << i << " j : " << j << " cost : " << cost << endl;

                    if(i == j || lo + 1 != hi) {
                        res = min(res, cost + mat[i][j]);
                    }
                }
            }
            cout << res << '\n';            
        }
    }

    return 0;
}
