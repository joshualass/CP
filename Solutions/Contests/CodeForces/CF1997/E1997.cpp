#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
template<typename T>
struct InvertedTree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    InvertedTree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void set(int pos, T val) {
        s[pos + n] = val;
    }
    void update(int l, int r, T u) { //increases values in [l,r) by u
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                s[l] = f(s[l],u);
                l++;
            }
            if(r & 1) {
                r--;
                s[r] = f(s[r],u);
            }
        }
    }
    T query(int pos) { //queries the value of element at pos
        T ans = s[pos += n];
        while(pos /= 2) {
            ans = f(ans,s[pos]);
        }
        return ans;
    }
};



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);

    for(int &x : a) cin >> x;

    vector<int> res(n);
    InvertedTree<int> tree(n);

    for(int i = 0; i < n; i++) {

        int l = 0, r = n;
        while(l != r) {
            int m = (l + r) / 2;
            int k = m + 1;
            int currstrength = 1 + tree.query(m) / k;
            if(currstrength > a[i]) {
                l = m + 1;
            } else {
                r = m;
            }

        }
        tree.update(l,n,1);
        res[i] = l;

    }

    // cout << "Res : " << res << '\n';

    for(int ii = 0; ii < q; ii++) {
        int i, x; cin >> i >> x;

        cout << (x > res[i - 1] ? "Yes" : "No") << '\n';

    }

    return 0;
}