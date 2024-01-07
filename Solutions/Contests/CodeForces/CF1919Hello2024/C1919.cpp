#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = {0,-1};
    T f(T a, T b) {
        if(a.first > b.first) {
            return a;
        } else {
            return b;
        }
        // return max(a,b); //update this function for different types of queries, currently sum
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) {
        cin >> x;
        x--;
    }
    Tree<pair<int,int>> twee(n);
    vector<int> prevs(n,-1);
    for(int i = 0; i < n; i++) {
        pair<int,int> p = twee.query(v[i],n);
        prevs[i] = p.second;
        // twee.update({v[i],i},twee.query(v[i],n)+1);
        twee.update(v[i], {p.first + 1, i});
    }

    pair<int,int> start = twee.query(0,n);
    vector<int> a;
    vector<int> b;
    vector<bool> visited(n);

    int i = start.second;
    while(i != -1) {
        // cout << "i : " << i << '\n';
        a.push_back(v[i]);
        visited[i] = 1;
        i = prevs[i];
    }
    reverse(a.begin(),a.end());
    for(int i = 0; i < n; i++) {
        if(!visited[i]) b.push_back(v[i]);
    }
    int cnt = 0;
    for(int i = 0; i < ((int) a.size()) - 1; i++) {
        if(a[i] < a[i+1]) cnt++;
    }
    for(int i = 0; i < ((int) b.size()) - 1; i++) {
        if(b[i] < b[i+1]) cnt++;
    }
    cout << "a : " << a << "\n";
    cout << "b : " << b << '\n';
    cout << cnt << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}