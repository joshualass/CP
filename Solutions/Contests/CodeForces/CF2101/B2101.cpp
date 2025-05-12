#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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

ll get_inv(vector<int> p, int n) {
    Tree<int> tree(n);
    ll res = 0;
    for(int i = 0; i < p.size(); i++) {
        res += tree.query(p[i] + 1, n);
        tree.update(p[i], 1);
    }
    // cout << "p : " << p << '\n';
    // cout << "res : " << res << '\n';
    return res;
}

void solve() {
    
    int n; cin >> n;
    vector<array<int,2>> o, e;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        if(i & 1) {
            o.push_back({x,i});
        } else {
            e.push_back({x,i});
        }
    }

    vector<int> b(n);
    sort(e.begin(), e.end());
    sort(o.begin(), o.end());
    vector<int> oi, ei;

    for(int i = 0; i < n; i++) {
        if(i & 1) {
            b[i] = o[i/2][0];   
            oi.push_back(o[i/2][1] / 2);
        } else {
            b[i] = e[i/2][0];
            ei.push_back(e[i/2][1] / 2);
        }
    }

    // cout << "b : " << b << '\n';

    // cout << "e : " << e << '\n';

    // cout << "oi : " << oi << '\n';
    // cout << "ei : " << ei << '\n';

    ll invo = get_inv(oi, oi.size()), inve = get_inv(ei, ei.size());
    // cout << "invo : " << invo << " inve : " << inve << '\n';

    if(invo % 2 != inve % 2) swap(b[n-1],b[n-3]);

    for(int x : b) cout << x + 1 << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n), ai(n);
//     set<int> e, o;
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         a[i] = x;
//         ai[x] = i;
//         if(i & 1) {
//             o.insert(x);
//         } else {
//             e.insert(x);
//         }
//     }

//     auto swap_2 = [&](int i, int j) -> void {
//         int ival = a[i], jval = a[j];
//         swap(a[i], a[j]);
//         swap(ai[ival], ai[jval]);
//     };

//     auto sim_q = [&](int i) -> void {
//         swap_2(i, i + 2);
//         swap_2(i + 1, i + 3);
//     };

//     cout << "start a : " << a << '\n';

//     for(int i = 0; i + 3 < n; i++) {
//         int t;
//         if(i & 1) {
//             t = *o.begin();
//             o.erase(t);
//         } else {
//             t = *e.begin();
//             e.erase(t);
//         }
//         int idx = ai[t];
//         if(((idx / 2) & 1) != ((i / 2) & 1)) {
//             sim_q(idx - 2);
//         }
//         idx = ai[t];
//         swap_2(i, idx);
//         cout << "i : " << i << " next a : " << a << '\n';
//     }

//     for(int x : a) cout << x + 1 << " ";
//     cout << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }