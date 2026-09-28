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
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    ll res = 0;

    Tree<int> tree(n);
    for(int i = 0; i < n; i++) {
        int ops = tree.query(a[i] + 1, n);
        tree.update(a[i], 1);

        ll hi = i, lo = hi - ops + 1;

        res += (hi + lo) * ops / 2;

    }

    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) {
//         cin >> x;
//         x--;
//     }

//     priority_queue<int, vector<int>, greater<int>> pq;

//     int l = 0;
//     ll res = 0;

//     for(int i = 0; i < n; i++) {
//         pq.push(a[i]);
//         while(pq.size() && pq.top() <= i) {
//             pq.pop();
//             l++;
//         }
//         int ops = (i + 1) - l, cost = i + 1;
//         res += 1LL * ops * cost;
//     }

//     cout << res << '\n';

//     return 0;
// }
