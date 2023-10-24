#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster
 
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
 
void solve() {
    int n; cin >> n;
    pb_map<int,queue<int>> m;
    Tree tree(n);
    vector<int> v(n);
    set<int> visited;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(m.find(num) == m.end()) {
            queue<int> q;
            q.push(i);
            m[num] = q;
            tree.update(i,1);
        } else {
            m[num].push(i);
        }
        v[i] = num;
    }
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(visited.find(v[i]) == visited.end()) {
            sum += tree.query(i,n);
        }
        visited.insert(v[i]);
        int remove = v[i];
        tree.update(i,0);
        m[v[i]].pop();
        if(m[v[i]].size()) {
            tree.update(m[v[i]].front(),1);
        }
    }
    cout << sum << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int casi; cin >> casi;
    while(casi-->0) solve();
 
    return 0;
}