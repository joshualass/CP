//https://open.kattis.com/problems/megainversions
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

struct custom_sort {
    template<typename T>
    bool operator()(const T &left, const T &right) {
        return left > right;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll ans = 0;
    Tree tree1(n), tree2(n);
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = {num,i};
    }
    sort(v.begin(),v.end(), custom_sort());
    for(int i = 0; i < n; i++) {
        int idx = v[i].second;
        tree1.update(idx,1LL);
        tree2.update(idx,tree1.query(0,idx));
        ans += tree2.query(0,idx);
    }
    cout << ans << "\n";
    return 0;
}