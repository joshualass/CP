// https://open.kattis.com/problems/studentsko

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    //typedef int T; //update the data type, currently int. often update to ll. Other way to do if needed
    static constexpr T base = 0;
    T f(T a, T b) {
        return max(a,b); //update this function for different types of queries, currently sum
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
    
    int n, k; cin >> n >> k;

    vector<pair<int,int>> v(n);

    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(), v.end());

    vector<int> order(n);
    for(int i = 0; i < n; i++) {
        order[v[i].second] = i / k;
    }

    //fill from the back and move around from there

    // cout << order << '\n';

    //problem is transformed into a longest increasing subsequence problem 
    //longest non-increasing subsequence starting from the back

    Tree<int> tree(n / k);

    for(int i = n - 1; i >= 0; i--) {

        tree.update(order[i], tree.query(order[i], n / k) + 1);

    }

    cout << n - tree.query(0, n / k) << '\n';

    return 0;
}