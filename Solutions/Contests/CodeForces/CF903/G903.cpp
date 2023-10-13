#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Tree {
    typedef int T; //update the data type, currently int. often update to ll
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tree &t) {
    for(auto x : t.s) os << x << " ";
    return os;
}

void solve() {
    int n, q; cin >> n >> q;
    string str; cin >> str;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = str[i] - 'a';
    }
    // cout << v << "\n";
    Tree adj(n-1);
    Tree adj1(n-2);
    for(int i = 0; i < n - 1; i++) {
        adj.update(i,v[i] == v[i+1]);
    }
    for(int i = 0; i < n - 2; i++) {
        adj1.update(i,v[i] == v[i+2]);
    }
    // cout << "adj: " << adj << "\n";
    // cout << "adj1: " << adj1 << "\n";
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int l, r, x; cin >> l >> r >> x;
            l--; r--; x %= 26;
            //update values, works as intended
            for(int j = l; j <= min(l + 1, r); j++) {
                // cout << "l: " << l << " r: " << r << " updating index: " << j << "\n";
                v[j] = (v[j] + x) % 26;
            }
            for(int j = max(l+2,r-1); j <= r; j++) {
                // cout << "l: " << l << " r: " << r << " updating index: " << j << "\n";
                v[j] = (v[j] + x) % 26;
            }
            //update segment trees
            //update l part
            for(int j = l - 1; j < l; j++) {
                if(j + 1 < n && j >= 0) {
                    // cout << "l: " << l << " r: " << r << " updating for length 2 at index: " << j << "\n";
                    adj.update(j,v[j] == v[j+1]);
                }
            }
            for(int j = l - 2; j < l; j++) {
                if(j + 2 < n && j >= 0) {
                    // cout << "l: " << l << " r: " << r << " updating for length 3 at index: " << j << "\n";
                    adj1.update(j,v[j] == v[j+2]);
                }
            }
            //update r part
            for(int j = r; j <= r; j++) {
                if(j + 1 < n && j >= 0) {
                    // cout << "l: " << l << " r: " << r << " updating for length 2 at index: " << j << "\n";
                    adj.update(j,v[j] == v[j+1]);
                }
            }
            for(int j = r - 1; j <= r; j++) {
                if(j + 2 < n && j >= 0) {
                    // cout << "l: " << l << " r: " << r << " updating for length 3 at index: " << j << "\n";
                    adj1.update(j,v[j] == v[j+2]);
                }
            }
        } else if(type == 2) {
            int l, r; cin >> l >> r;
            l--;
            // cout << "adj: " << adj << "\n";
            // cout << "adj1: " << adj1 << "\n";
            // cout << "l: " << l << " r: " << r << "\n";
            if(adj.query(l,r-1) > 0 || adj1.query(l,r-2) > 0) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
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