#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return max(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node];
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            int mid = (currl + currr) / 2;
            return query_comb(
                _query(node * 2, currl, mid, targetl, targetr),
                _query(node * 2 + 1, mid, currr, targetl, targetr)
            );
        }
    }
};

int lifts[200000][20];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> tin(n), tout(n), d(n);
    int time = 0;
    auto dfs1 = [&](auto self, int i, int p, int depth) -> void {
        tin[i] = time++;
        d[i] = depth;
        lifts[i][0] = p;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, depth + 1);
            }
        }
        tout[i] = time;
    };

    dfs1(dfs1, 0, 0, 0);

    // cout << "tin : " << tin << '\n';
    // cout << "tout : " << tout << '\n';

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[j][i] = lifts[lifts[j][i-1]][i-1];
        }
    }

    auto upk = [&](int a, int k) -> int {
        for(int i = 0; i < 20; i++) {
            if((k >> i) & 1) {
                a = lifts[a][i];
            }
        }
        return a;
    };

    vector<vector<pair<int,vector<int>>>> queries(n);
    for(int i = 0; i < q; i++) {
        int x, k; cin >> x >> k;
        x--;
        queries[x].push_back({i,{}});
        for(int j = 0; j < k; j++) {
            int y; cin >> y;
            queries[x].back().second.push_back(y-1);
        }
    }

    Lazy<int,int> lazy(n);
    for(int i = 0; i < n; i++) {
        lazy.update(tin[i],tin[i]+1,d[i]);
    }

    vector<int> res(q);

    auto dfs2 = [&](auto self, int i, int p) -> void {
        if(i) {
            lazy.update(tin[i], tout[i], -2);
            lazy.update(0,n,1);
        }

        // cout << "i : " << i << '\n';
        // for(int j = 0; j < n; j++) {
        //     cout << "dist from node j, " << j << " is : " << lazy.query(tin[j],tin[j]+1) << '\n';
        // }

        for(auto [id, removals] : queries[i]) {
            map<int,int> m;
            for(int removal : removals) {
                if(d[removal] < d[i] && upk(i,d[i]-d[removal]) == removal) {
                    int allowedsubtree = upk(i,d[i]-d[removal]-1);
                    m[0]++;
                    m[tin[allowedsubtree]]--;
                    m[tout[allowedsubtree]]++;
                    m[n]--;
                } else {
                    m[tin[removal]]++;
                    m[tout[removal]]--;
                }
            }

            int ans = 0;
            int previdx=0;
            int cnt = 0;

            // cout << "query id : " << id << '\n';
            // cout << "map : " << m << '\n';

            for(auto [idx, a] : m) {
                if(cnt == 0) {
                    // cout << "query range : " << previdx << " to " << idx << '\n';
                    ans = max(ans, lazy.query(previdx, idx));
                }
                cnt += a;
                if(cnt == 0) {
                    previdx = idx;
                }
            }
            // cout << "query range : " << previdx << " to " << n << '\n';
            ans = max(ans, lazy.query(previdx,n));
            res[id] = ans;
        }

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }

        if(i) {
            lazy.update(tin[i], tout[i], 2);
            lazy.update(0,n,-1);
        }
    };  

    dfs2(dfs2, 0, -1);

    for(int x : res) cout << x << '\n';

    return 0;
}