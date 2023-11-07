#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

    int find_index(T val) {
        if(s[1] < val) return 0;
        int lo = 0, hi = n;
        while(lo != hi) { //searching for FFFFFTTTTT first true
            int m = (lo + hi + 1) / 2;
            if(query(0,m) < val) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        update(lo, s[lo+n] - val);
        return lo + 1;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    Tree<int> tree(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        tree.update(i,num);
    }
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        cout << tree.find_index(num) << " ";
    }

    return 0;
}