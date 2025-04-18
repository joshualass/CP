#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> ai(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        ai[x] = i;
    }

    Tree<int> tree(n);
    for(int i = 0; i < n; i++) tree.update(i, 1);
    for(int l = 0, r = n - 1; l <= r;) {
        cout << tree.query(0, ai[l]) << '\n';
        tree.update(ai[l++], 0);
        if(l <= r) {
            cout << tree.query(ai[r] + 1, n) << '\n';
            tree.update(ai[r--], 0);
        }
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const int N = 1e5;
// int n;
// int t[2 * N];

// void build() {
//     for (int i = n - 1; i > 0; --i) {
//         t[i] = t[i * 2] + t[i * 2 + 1];
//     }
// }

// void modify(int p, int value) {
//     p += n;
//     t[p] = value;
//     while(p > 1) {
//         t[p / 2] = t[p] + t[p ^ 1];
//         p /= 2;
//     }
// }

// int query(int l, int r) {// l inclusive, r exclusive, 0 indexed
//     int ans = 0;
//     l += n;
//     r += n;
//     while(l < r) {
//         if (l % 2 == 1) {
//             ans += t[l];
//             l++;
//         }
//         if (r % 2 == 1) {
//             r--;
//             ans += t[r];
//         }
//         l /= 2;
//         r /= 2;
//     }
//     return ans;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     cin >> n;
//     map<int,int> m;
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         m[--num] = i;
//         modify(i, 1);
//     }
//     for(int l = 0; l < n; l++) {
//         int i = l/2;
//         if(l % 2) {
//             int temp = n - i - 1;
//             int index = m[temp];
//             cout << query(index + 1,n) << "\n";
//             modify(index,0);
//         } else {
//             int index = m[i];
//             cout << query(0,index) << "\n";
//             modify(index,0);
//         }
//     }

//     return 0;
// }