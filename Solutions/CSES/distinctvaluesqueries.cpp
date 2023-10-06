#include <bits/stdc++.h>
typedef long long ll;
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
    unordered_map<int,queue<int>> m;
    vector<int> v(n);
    Tree tree(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(m.find(num) == m.end()) {
            tree.update(i,1);
            queue<int> Q;
            Q.push(i);
            m[num] = Q; 
        } else {
            m[num].push(i);
        }
        v[i] = num;
    }
    vector<vector<int>> queries(q);
    vector<int> ans(q);
    // for(auto &x: queries) cin >> x.first >> x.second, x.first--;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l --;
        queries[i] = {l,r,i};
    }
    sort(queries.begin(),queries.end());
    int idx = 0;
    for(int i = 0; i < q; i++) {
        while(idx < n && queries[i][0] > idx) {
            int update = v[idx++];
            m[update].pop();
            // cout << "exist? " << (m.find(update) != m.end()) << " size: " << m[update].size() << "\n";
            if(m[update].size() > 0) {
                tree.update(m[update].front(),1);
            }
        }
        // cout << tree.query(queries[i].first,queries[i].second) << "\n";
        ans[queries[i][2]] = tree.query(queries[i][0],queries[i][1]);
    }
    for(auto &x: ans) cout << x << "\n";
    return 0;
}