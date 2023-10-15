#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
struct InvertedTree {
    typedef int T; //update the data type, currently int. often update to ll
    static constexpr T base = 0;
    T f(T a, T b) {
        return (a + b) % 26; //update this function for different types of queries, currently sum
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
        return ans % 26;
    }
};

template<typename T>
struct Tree {
    //typedef int T; //update the data type, currently int. often update to ll. Other way to do if needed
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
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
        if(r <= l) return base;
        T ans = base;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) ans = f(ans, s[l++]);
            if(r & 1) ans = f(s[--r],ans);
        }
        return ans;
    }
};

InvertedTree invertedTree(2e5 + 1);
Tree<int> tree2(2e5 + 1);
Tree<int> tree3(2e5 + 1);

void solve() {
    int n, m; cin >> n >> m;
    string str; cin >> str;
    invertedTree.n = n;
    if(n > 1) {
        tree2.n = n - 1;
        if(n > 2) {
            tree3.n = n - 2;
        }
    }
    for(int i = 0; i < n; i++) {
        invertedTree.update(i,i+1,str[i] - 'a');
    }
    for(int i = 0; i < n-1; i++) {
        if(invertedTree.query(i) == invertedTree.query(i+1)) tree2.update(i,1);
    }
    for(int i = 0; i < n - 2; i++) {
        if(invertedTree.query(i) == invertedTree.query(i+2)) tree3.update(i,1);
    }
    for(int i = 0; i < m; i++) {
        int type; cin >> type;
        if(type == 1) {
            int l, r, x; cin >> l >> r >> x;
            l--; x%= 26;
            invertedTree.update(l,r,x);
            if(l != 0) {
                tree2.update(l-1,invertedTree.query(l-1) == invertedTree.query(l));
            }
            if(l != 0 && l + 1 < n) {
                tree3.update(l-1,invertedTree.query(l-1) == invertedTree.query(l+1));
            }
            if(l > 1) {
                tree3.update(l-2,invertedTree.query(l-2) == invertedTree.query(l));
            }
            r--;
            // if(r != 0) {
            //     tree2.update(r-1,invertedTree.query(r-1) == invertedTree.query(r));
            // }
            // if(r != 0 && r + 1 < n) {
            //     tree3.update(r-1,invertedTree.query(r-1) == invertedTree.query(r+1));
            // }
            // if(r > 1) {
            //     tree3.update(r-2, invertedTree.query(r-2) == invertedTree.query(r));
            // }
            if(r + 1 < n) {
                tree2.update(r,invertedTree.query(r) == invertedTree.query(r+1));
            }
            if(r + 2 < n) {
                tree3.update(r,invertedTree.query(r) == invertedTree.query(r+2));
            }
            if(r != 0 && r+1 < n) {
                tree3.update(r-1,invertedTree.query(r-1) == invertedTree.query(r+1));
            }
        } else if(type == 2) {
            int l, r; cin >> l >> r;
            l--;
            // cout << "q2: " << tree2.query(l,r-1) << " q3: " << tree3.query(l,r-2) << "\n";
            if(tree2.query(l,r-1) || tree3.query(l,r-2)) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        }
    }

    fill(invertedTree.s.begin(),invertedTree.s.begin() + n * 2 + 1,0);
    if(n > 1) {
        fill(tree2.s.begin(),tree2.s.begin() + (n - 1) * 2 + 1, 0);
        if(n > 2) {
            fill(tree3.s.begin(),tree3.s.begin() + (n - 2) * 2 + 1, 0);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}