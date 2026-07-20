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

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

const int MAXLEN = 2000001;
template <int len = 1>
vector<int> small_m(int n, int m, vector<string> &a) {
    if(n > len) {
        return small_m<min(len * 2, MAXLEN)>(n, m, a);
    }

    vector<bitset<len>> b;
    for(int i = 0; i < m; i++) {
        bitset<len> cur {};
        for(int j = 0; j < n; j++) {
            cur[j] = a[j][i] - '0';
        }
        b.push_back(cur);
    }

    vector<int> res;

    for(int i = 0; i < m; i++) {
        bitset<len> cur {};
        cur.set();
        for(int j = 0; j < m; j++) {
            if((cur & b[(i + j) % m]).any()) {
                cur &= b[(i + j) % m];
            }
        }
        assert(cur.count() == 1);
        for(int j = 0; j < n; j++) {
            if(cur[j]) res.push_back(j);
        }
    }

    return res;
}

// struct Tree {
//     typedef pair<vector<vector<int>>, vector<int>> T;
//     T base = {};
//     vector<T> v;
//     int n, size;
//     int dim;

//     T f(T a, T b) { //change this when doing maximum vs minimum etc.

//         int buckets = sz(b.first);
//         vector<vector<array<int,2>>> bc(buckets); // {group, cnt}
//         vector<vector<int>> atbucket(buckets);

//         for(int i = 0; i < sz(a.first); i++) {
//             for(int x : a.first[i]) {
//                 int bucket = b.second[x];
//                 atbucket[bucket].push_back(x);
//                 if(bc[bucket].empty() || bc[bucket].back()[0] != i) {
//                     bc[bucket].push_back({i, 0});
//                 }
//                 bc[bucket].back()[1]++;
//             }
//         }

//         vector<vector<vector<int>>> ng(sz(a.first));

//         for(int i = 0; i < buckets; i++) {
//             int cur = 0;
//             for(auto [group, cnt] : bc[i]) {
//                 ng[group].push_back({});
//                 for(int j = 0; j < cur; j++) {
//                     ng[group].back().push_back(atbucket[i][cur++]);
//                 }
//             }
//         }

//         vector<int> res(dim);
//         vector<vector<int>> resb;

//         for(int i = 0; i < sz(a.first); i++) {
//             for(int j = 0; j < sz(ng[i]); j++) {
//                 resb.push_back({});
//                 for(int x : ng[i][j]) {
//                     resb.back().push_back(x);
//                     res[x] = sz(resb) - 1;
//                 }
//             }
//         }

//         return {resb, res};
//     }

//     Tree(int n, T def) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     Tree(vector<T> a, int dim) {
//         this->n = sz(a); //max number of elements
//         this->dim = dim;
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

typedef pair<int, vector<int>> T;
void merge(vector<vector<int>> &a, T &b, int dim) { //change this when doing maximum vs minimum etc.

    // cout << "merge called" << endl;
    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;
    // cout << "dim : " << dim << endl;

    int buckets = b.first;

    // cout << "buckets : " << buckets << endl;
    vector<vector<array<int,2>>> bc(buckets); // {group, cnt}
    vector<vector<int>> atbucket(buckets);

    for(int i = 0; i < sz(a); i++) {
        for(int x : a[i]) {
            int bucket = b.second[x];
            atbucket[bucket].push_back(x);
            if(bc[bucket].empty() || bc[bucket].back()[0] != i) {
                bc[bucket].push_back({i, 0});
            }
            bc[bucket].back()[1]++;
        }
    }

    // cout << "bc : " << bc << endl;
    // cout << "atbucket : " << atbucket << endl;

    vector<vector<vector<int>>> ng(sz(a));

    for(int i = 0; i < buckets; i++) {
        int cur = 0;
        for(auto [group, cnt] : bc[i]) {
            ng[group].push_back({});
            for(int j = 0; j < cnt; j++) {
                ng[group].back().push_back(atbucket[i][cur++]);
            }
        }
    }

    // cout << "ng : " << ng << endl;

    vector<int> res(dim);
    int res_dim = 0;

    for(int i = 0; i < sz(a); i++) {
        for(int j = 0; j < sz(ng[i]); j++) {
            res_dim++;
            for(int x : ng[i][j]) {
                res[x] = res_dim - 1;
            }
        }
    }

    // cout << "resb : " << resb << " res : " << res << endl;
    // auto res = {resb, res};
    // return {resb, res};
    b = {res_dim, res};
}

vector<int> ttfang(int n, int m, vector<string> &a) {
    T cur = {1, vector<int>(n)};
    vector<int> res(m);
    
    for(int i = m * 2 - 1; i >= 0; i--) {
        vector<vector<int>> buckets(2);
        for(int j = 0; j < n; j++) {
            int x = (a[j][i % m] - '0') ^ 1;
            buckets[x].push_back(j);
        }

        merge(buckets, cur, n);
        if(i < m) {
            for(int j = 0; j < n; j++) {
                if(cur.second[j] == 0) res[i] = j + 1;
            }
        }
    }

    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    // cout << small_m(n, m, a) << '\n';

    cout << ttfang(n, m, a) << '\n';


    return 0;
}
