#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; //stores the starting values at all nodes, 
    static constexpr D ln = {0,0};
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //base, count of how many polynomials start at one at the beginning of this node
    int n, size;

    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {
        return node >= size;
    }
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        // cout << "lcomb : " << node << " val : " << val << '\n';
        lazy[node].first += val.first;
        lazy[node].second += val.second; 
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node].first * size;
        v[node] += lazy[node].second * size * (size + 1) / 2;
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, {lazy[node].first + lazy[node].second * size / 2, lazy[node].second});
        }
        lazy[node] = ln;
    }
    void update(int l, int r) {
        _update(1,0,size,l,r);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr) {
        // cout << "node : " << node << " currl : " << currl << " currr : " << currr << " tl : " << targetl << " tr : " << targetr << '\n';
        push_lazy(node, currr - currl);
        if (currl >= targetr || currr <= targetl) return;
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, {currl - targetl,1}); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr);
            _update(node * 2 + 1, mid, currr, targetl, targetr);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) {
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr)return qn; 
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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<ll> pre(n+1);
    for(int i = 1; i <= n; i++) {
        ll num; cin >> num;
        pre[i] = pre[i-1] + num;
    }

    Lazy<ll,pair<ll,ll>> lazy(n);
    ll sum = 0;

    for(int i = 0; i < q; i++) {
        int type, a, b; cin >> type >> a >> b;
        if(type == 1) {
            sum += (b - a + 1) * (b - a + 2) / 2;
            lazy.update(a-1,b);
        }
        if(type == 2) {
            cout << lazy.query(a-1,b) + pre[b] - pre[a-1] << '\n';
        }
        // cout << "v\n" << lazy.v << '\n';
        // cout << "lazy\n" << lazy.lazy << '\n';
        // cout << "sum : " << sum << " lazytop : " << lazy.v[1] << '\n';
    }

    return 0;
}