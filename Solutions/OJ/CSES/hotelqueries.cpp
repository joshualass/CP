// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// struct Tree {
//     //typedef int T; //update the data type, currently int. often update to ll. Other way to do if needed
//     static constexpr T base = 0;
//     T f(T a, T b) {
//         return max(a,b); //update this function for different types of queries, currently sum
//     }
//     vector<T> s; int n;
//     Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
//     void build() {
//         for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
//     }
//     void update(int pos, T val) {
//         for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
//     }
//     T query(int l, int r) { //[l,r)
//         T ans = base;
//         for(l += n, r += n; l < r; l /= 2, r /= 2) {
//             if(l & 1) ans = f(ans, s[l++]);
//             if(r & 1) ans = f(s[--r],ans);
//         }
//         return ans;
//     }

//     int find_index(T val) {
//         if(s[1] < val) return 0;
//         int lo = 0, hi = n;
//         while(lo != hi) { //searching for FFFFFTTTTT first true
//             int m = (lo + hi + 1) / 2;
//             if(query(0,m) < val) {
//                 lo = m;
//             } else {
//                 hi = m - 1;
//             }
//         }
//         update(lo, s[lo+n] - val);
//         return lo + 1;
//     }

// };

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     Tree<int> tree(n);
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         tree.update(i,num);
//     }
//     for(int i = 0; i < m; i++) {
//         int num; cin >> num;
//         cout << tree.find_index(num) << " ";
//     }

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
struct SegTreeLQ {
    static constexpr T base = 0; //change this when doing maximum vs minimum etc.
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b); 
    }

    bool cond(T a, T b) {
        return a <= b; //change this when doing maximum vs minimum etc.
    }
    vector<T> v;
    int n = -1, size = -1;

    SegTreeLQ(int n = 0, T def = base) {
        this->n = n; //max number of elements
        this->size = 1 << (31 - __countl_zero(n) - (int)(__builtin_popcount(n) == 1)); //size of vector
        v.assign(size * 2, base);
    }

    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            v[curr/2] = comb(v[curr], v[curr ^ 1]);
            curr /= 2;
        }
    }

    bool isLeaf(int idx) {
        return idx >= size;
    }

    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> query(T val, int lo, int hi) {
        if(lo >= hi) return {-1,base}; //starting pos is OOB
        lo = max(lo,0);
        hi = min(hi,n);
        pair<int,T> ans = _query(1, lo, hi, val);
        if(ans.first >= 0) {
            update(ans.first, v[ans.first + size] - val);
        }
        return ans;
    }   

    pair<int,T> query(T val, int lo) {
        return query(val,lo,n);
    }   

    pair<int,T> query(T val) {
        return query(val, 0, n);
    }

    pair<int,T> _query(int idx, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(isLeaf(idx)) {
            if(cond(val, v[idx])) { // in case length is 1 and index is invalid
                return {idx - size, v[idx]};
            } else {
                return {-1,base};
            }
        }
        int shift = __countl_zero(idx) - __countl_zero(size);
        int left_lo = (idx << shift) - size;
        int left_hi = left_lo + (1 << (shift - 1));
        int right_lo = left_hi;
        int right_hi = right_lo + (1 << (shift - 1));

        //overlap in left and an answer exists, doesn't necessarily mean a solution
        if(left_hi > lo && cond(val, v[idx * 2])) {
            // cout << " go left \n";
            pair<int,T> ans = _query(idx * 2, lo, hi, val);
            if(ans.first != -1) return ans;
        }
        //overlap in right and an answer exists
        if(right_lo < hi && cond(val, v[idx * 2 + 1])) {
            // cout << " go right \n";
            return _query(idx * 2 + 1, lo, hi, val);
        }

        return {-1,base}; //nooverlap in both sides/doesn't exist
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    SegTreeLQ<int> tree(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        tree.update(i, num);
    }

    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        pair<int,int> p = tree.query(num,0,n);
        cout << p.first + 1 << " ";
    }


    return 0;
}