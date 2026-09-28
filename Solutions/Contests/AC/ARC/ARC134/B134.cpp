#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = INT_MAX;
    T f(T a, T b) {
        return min(a,b); //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void build() {
        for(int i = n - 1; i > 0; i--) s[i] = f(s[i*2],s[i*2+1]);
    }
    void update(int pos, T val) {
        for(s[pos += n] = val; pos /= 2;) s[pos] = f(s[pos*2],s[pos*2+1]);
    }
    T query(int l, int r) { //[l,r)
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string str; cin >> str;

    Tree<int> tree(n);

    for(int i = 0; i < n; i++) {
        tree.update(i,str[i]);
    }

    int lo = 0;

    //character at lo index is already best
    while(lo < n && str[lo] <= tree.query(lo,n)) {
        lo++;
    }
    // cout << "lo: " << lo << '\n';
    for(int hi = n - 1; hi > lo; hi--) {
        // cout << "lo: " << lo << " hi: " << hi << " str: " << str << '\n';
        if(tree.query(lo,hi+1) >= str[hi]) {
            swap(str[hi],str[lo]);
            tree.update(lo, str[lo]);
            tree.update(hi,str[hi]);
            lo++;
            while(lo < n && str[lo] <= tree.query(lo,hi)) {
                lo++;
            }
        } else {
            while(lo < n && str[lo] <= tree.query(lo,hi+1)) {
                lo++;
            }
        }

    }

    cout << str << '\n';

    return 0;
}