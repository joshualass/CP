//is there a way to solve without using compression?
//YES, just use an ordered_set ... and order_of_key cheatcode
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
    vector<int> v(n);
    vector<int> seen(0);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i] = num;
        seen.push_back(num);
    }
    vector<pair<char,pair<int,int>>> queries(q);
    for(int i = 0; i < q; i++) {
        char Q; cin >> Q;
        int a, b; cin >> a >> b;
        queries[i] = {Q,{a,b}};
        if(Q == '!') seen.push_back(b);
    }
    sort(seen.begin(),seen.end());
    map<int,int> m;
    int curr = 0;
    for(int i = 0; i < seen.size(); i++) {
        if(m.find(seen[i]) == m.end()) {
            m[seen[i]] = curr++;
        }
    }
    Tree tree(m.size());
    for(int i = 0; i < n; i++) {
        v[i] = m[v[i]];
        tree.update(v[i], tree.s[v[i] + m.size()]+1);
    }
    for(int i = 0; i < q; i++) {
        pair<int,int> p = queries[i].second;
        if(queries[i].first == '!') {
            //remove previous, the salary at index of p.first
            p.first--;
            tree.update(v[p.first], tree.s[v[p.first] + m.size()] - 1);
            //add new
            v[p.first] = m[p.second];
            tree.update(v[p.first], tree.s[v[p.first] + m.size()] + 1);
        } else {
            if(m.lower_bound(p.first) == m.end()) {
                cout << "0\n";
            } else {
                int l = (*m.lower_bound(p.first)).second;
                int r;
                if(m.upper_bound(p.second) == m.end()) {
                    r = m.size();
                } else {
                    r = (*m.upper_bound(p.second)).second;
                }
                cout << tree.query(l,r) << "\n";
            }

        }
    }

    return 0;
}