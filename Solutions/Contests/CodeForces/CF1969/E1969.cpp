#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
we do not want to do divide and conquer because that's n logn logn and annoying to implement
let's try iterating through and the points and make sure that at each point, all the ranges ending at i are satisfied
we will do this with an increment modify, minimum query lazy seg tree
uses greedy approach which should work
*/

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = INT_MAX; //stores the starting values for queries
    static constexpr D ln = 0;
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
        return min(val1,val2);
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
    void update(int l, int r, D val) {
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
    T query(int l, int r) {
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

void solve() {
    
    int n; cin >> n;
    Lazy<int,int> lazy(n,0);

    map<int,pair<int,int>> prevs;
    int ops = 0;
    int lo = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(prevs.count(num)) {
            pair<int,int> p = prevs[num];
            lazy.update(p.first,p.second,-1);
            lazy.update(p.second, i+1,1);
            prevs[num] = {p.second, i+1};
        } else {
            lazy.update(lo,i+1,1);
            prevs[num] = {lo,i+1};
        }
        int v = lazy.query(lo,i+1);
        if(v == 0) {
            ops++;
            lo = i + 1;
            prevs.clear();
        }
    }
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;



// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);
//     map<int,vector<int>> pivots;
//     for(int i = 0; i < n; i++) {
//         cin >> a[i];
//         pivots[a[i]].push_back(i);
//     }

//     vector<int> points;
//     for(auto x : pivots) {
//         if(x.second.size() == 1) {
//             points.push_back(x.first);
//         }
//     }
//     points.push_back(-1);
//     points.push_back(n);


//     int cnt = 0;
//     map<int,int> m;
//     int onecnts = 0;
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         m[num]++;
//         if(m[num] == 1) onecnts++;
//         if(m[num] == 2) onecnts--;
//         if(onecnts == 0) {
//             cnt++;
//             m.clear();
//         }
//     }
//     cout << cnt << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }