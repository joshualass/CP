#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//static array - range minimum query can also be solved with a sparse table

struct Tree {
    typedef int T; //update the data type, currently int. often update to ll
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    Tree tree(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        tree.update(i,num);
    }
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << tree.query(a,b) << "\n";
    }

    return 0;
}