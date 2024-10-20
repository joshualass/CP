#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    string s; cin >> s;

    vector<int> maxprefs(n), minsuffs(n);

    for(int i = 0; i < n; i++) {
        maxprefs[i] = max(a[i], (i >= 1 ? maxprefs[i-1] : 0));
    }

    for(int i = n - 1; i >= 0; i--) {
        minsuffs[i] = min(a[i], (i < n - 1 ? minsuffs[i+1] : INT_MAX));
    }

    int cntbad = 0;

    auto isbad = [&](int i) -> int {
        // cout << "i : " << i << " val : " << (s[i] == 'L' && s[i+1] == 'R' && (maxprefs[i] > i + 1 || minsuffs[i+1] < i + 2)) << '\n';
        return s[i] == 'L' && s[i+1] == 'R' && (maxprefs[i] > i + 1 || minsuffs[i+1] < i + 2);
    };

    for(int i = 0; i < n - 1; i++) {
        cntbad += isbad(i);
    }

    for(int i = 0; i < q; i++) {
        int idx; cin >> idx;
        idx--;
        if(s[idx] == 'L') {
            cntbad -= isbad(idx);
            s[idx] = 'R';
            cntbad += isbad(idx-1);
        } else {
            cntbad -= isbad(idx-1);
            s[idx] = 'L';
            cntbad += isbad(idx);
        }

        cout << (cntbad ? "No" : "Yes") << '\n';
    }

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
// const ll MOD = 998244353;

// template<typename T>
// struct MaxTree {
//     static constexpr T base = INT_MIN;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a + b);
//     }
//     MaxTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
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
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// template<typename T>
// struct MinTree {
//     static constexpr T base = INT_MAX;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return min(a + b);
//     }
//     MinTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
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
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// void solve() {
//     int n, q; cin >> n >> q;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     string s; cin >> s;

//     MinTree<int> aMin(n);
//     MaxTree<int> aMax(n);

//     MaxTree<int> rChars(n);
//     MinTree<int> lChars(n);

//     for(int i = 0; i < n; i++) {
//         aMin.update(i, a[i]);
//         aMax.update(i, a[i]);

//         if(s[i] == 'L') {
//             lChars.update(i,i);
//         } else {
//             rChars.update(i,i);
//         }
//     }

//     int status = 0;




// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }