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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Tree &t) {
    for(auto x : t.s) os << x << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("haircut.in","r",stdin);
    freopen("haircut.out","w",stdout);
    
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first; v[i].second = i;
    }
    sort(v.rbegin(),v.rend()); //sorts in reverse order because reverse iterators in one line
    Tree tree(n,1); tree.build();
    ll invs = 0;
    // cout << tree << "\n";
    for(int i = 0; i < n; i++) {
        while(v.size() && v.back().first < i) {
            invs += tree.query(0,v.back().second);
            tree.update(v.back().second,0);
            v.pop_back();
        }
        cout << invs << "\n";
    }
    // cout << v << "\n";

    return 0;
}