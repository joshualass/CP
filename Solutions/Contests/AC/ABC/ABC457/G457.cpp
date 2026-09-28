#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

const array<int,3> def = {inf, 0, -1};
const int maxn = 600001;

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

int killed[300000];

struct Tree {
    typedef array<int,3> T;
    T base = def;
    vector<vector<T>> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a[1] - a[0] > b[1] - b[0]) {
            return a;
        } else {
            return b;
        }
    }
    Tree(int n) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].push_back(val);
        
        while(curr != 1) {
            curr /= 2;
            v[curr].push_back(val);
        }
    }
    vector<T> at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) {
            while(sz(v[idx]) && killed[v[idx].back()[2]]) v[idx].pop_back();
            if(sz(v[idx])) {
                return v[idx].back();
            } else {
                return base;
            }
        }
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
    vector<array<int,2>> a(n);

    for(auto &x : a) for(auto &y : x) cin >> y;

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {  
        return lhs[1] - lhs[0] < rhs[1] - rhs[0];
    });

    Tree tree(maxn);

    for(int i = 0; i < n; i++) {
        auto [x, y] = a[i];
        tree.update(x + y, {x, y, i});
    }

    auto pt = [&]() -> void {
        for(int i = 0; i < 18; i++) {
            cout << "i : " << i << " t at i : " << tree.at(i) << endl;
        }
    };

    // pt();

    int res = 0;

    while(n) {
        res++;

        // cout << "start robot res : " << res << " left : " << n << endl;

        auto check = [&](array<int,3> left, array<int,3> right) -> int {
            if(left == def || right == def) return 1;
            return abs(left[1] - right[1]) <= abs(left[0] - right[0]) && left[0] < right[0];
        };

        auto dnc = [&](auto self, array<int,3> left, array<int,3> right) -> void {
            // cout << "left : " <<left << " right : " << right << endl;
            if(left != def && right != def) {
                // cout << "check" << endl;
                // cout << "left : " <<left << " right : " << right << endl;
                // assert(left[0] < right[0]);
            }
            int l = left == def ? 0 : left[1] + left[0];
            int r = right == def ? maxn : right[1] + right[0] + 1;
            // cout << "l : " << l << " r : " << r << endl;
            array<int,3> q = tree.query(l, r);
            if(q != def && check(left, q) && check(q, right)) {
                n--;
                // cout << "kill " << q << endl;
                killed[q[2]] = 1;
                // pt();
                // cout << "match to robot : " << q << endl;
                self(self, q, right);
                self(self, left, q);
            }
        };
        dnc(dnc, def, def);
    }

    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()
// const int inf = 1e9;
// const int maxn = 3e5 + 1;

// const array<int,2> def = {-inf, -1};

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// template<typename T>
// struct Tree {
//     static constexpr T base = {-inf, -1};
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a, b);
//     }
//     Tree(int n, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     Tree(vector<T> a) {
//         this->n = sz(a); //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.resize(size * 2);
//         assert(n == sz(a));
//         for(int i = 0; i < n; i++) {
//             v[i + size] = a[i];
//         }
//         for(int i = size - 1; i >= 1; i--) {
//             v[i] = f(v[i * 2], v[i * 2 + 1]);
//         }
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<vector<int>> a(maxn);

//     for(int i = 0; i < n; i++) {
//         int t, x; cin >> t >> x;
//         a[t].push_back(x-t);
//     }

//     Tree<array<int,2>> tree(maxn);
//     for(int i = 0; i < maxn; i++) {
//         sort(a[i].begin(), a[i].end());
//         if(!a[i].empty()) {
//             tree.update(i, {a[i].back(), i});
//         }
//     }

//     int res = 0;

//     while(n) {
//         res++;

//         // cout << "start robot res : " << res << " left : " << n << endl;

//         auto check = [&](array<int,2> left, array<int,2> right) -> int {
//             if(left == def || right == def) return 1;
//             assert(left[1] <= right[1]);
//             int d = right[1] - left[1];
//             return left[0] >= right[0] && left[0] - d * 2 <= right[0];
//         };

//         auto dnc = [&](auto self, array<int,2> left, array<int,2> right) -> void {
//             // cout << "left : " <<left << " right : " << right << endl;
//             int l = left == def ? 0 : left[1] + 1;
//             int r = right == def ? maxn : right[1];
//             // cout << "l : " << l << " r : " << r << endl;
//             array<int,2> q = tree.query(l, r);
//             // cout << "q : " << q << endl;
//             if(q != def && check(left, q) && check(q, right)) {
//                 n--;
//                 int t = q[1];
//                 assert(!a[t].empty());
//                 a[t].pop_back();
//                 // cout << "match to robot : " << q << endl;
//                 if(!a[t].empty()) {
//                     tree.update(t, {a[t].back(), t});
//                 } else {
//                     tree.update(t, def);
//                 }
//                 self(self, left, q);
//                 self(self, q, right);
//             }
//         };
//         dnc(dnc, def, def);
//     }

//     cout << res << '\n';

//     return 0;
// }
