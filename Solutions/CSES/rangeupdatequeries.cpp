/* range updates, single element query. 
possible with a modified segment tree I hope.
TODO in platinum - lazy propagation
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Tree {
    typedef ll T; //update the data type, currently int. often update to ll
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
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

std::ostream& operator<<(std::ostream& os, const Tree &t) {
    for(auto x : t.s) os << x << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    Tree tree(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        tree.set(i,num);
    }
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll l, r, u; cin >> l >> r >> u;
            l--;
            tree.update(l,r,u);
        } else {
            int x; cin >> x;
            x--;
            cout << tree.query(x) << "\n";
        }
    }

    return 0;
}