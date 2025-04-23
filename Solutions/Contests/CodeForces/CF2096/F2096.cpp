#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
we want to do a sliding window approach to see for each L, the furthest R such that none of the impostor conditions are unsatisfied
Originally, we could maybe assign a value in the array for each of the impostor conditions and move these as we add crewmate conditions,
but it is nontrivial on how to move these crewmate conditions. 

instead, let's store each of the impostor things as intervals and not assign the actual indices of where they go. 
How to maintain the sliding window.
Use a lazy segment tree to store the intervals of crewmates with minimum query
Store the impostor in some DS so that we can add/remove impostor stuff and query the interval that ends the earliest, starting after some l. 

when adding right to sliding window
adding crewmate statement, add to the lazy segtree and find the longest contiguous interval of crewmate statements that include this statement
see if there is an impostor statement in this range to see if it's bad. 
adding impostors, we add to our ds and check with lazy seg min query

when removing crewmates, how do we see that all things are good? 
it means that previous condition requires a statement to be violated
if it's a crewmate that was added to a violation, we recalculate the left and right points and see if the impostors are bad.
If it's a impostor that was added to a violation, we see if it's satisfied now. 
Doesn't really matter what was removed. (left end)

all operations can be done in logn if we have a lazy segtree that supports miq

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 1e9; // query neutral, when we query, doing the operation with this value won't change our query
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
        // return val1 + val2;
        return min(val1, val2);
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
    bool F(T treeval, T targetval) {return treeval == 0;}
    int findFirst(int l, int r, T targetval) {
        return _findFirst(1, 0, size, l, r, targetval);
    }
    int _findFirst(int node, int cl, int cr, int tl, int tr, T tv) {
        if(cr <= tl || cl >= tr) return n;
        push_lazy(node, cr - cl); //almighty push!
        if(F(v[node], tv)) { //there exists something good in the range
            if(isLeaf(node)) {
                return cl;
            }
            //not a leaf, so try left and right
            int mid = (cl + cr) / 2;
            int left = _findFirst(node * 2, cl, mid, tl, tr, tv);
            if(left != n) return left;
            return _findFirst(node * 2 + 1, mid, cr, tl, tr, tv);
        } else { //nuffin good in this range, stop. 
            return n;
        }
    }
    int findLast(int l, int r, T targetval) {
        return _findLast(1, 0, size, l, r, targetval);
    }
    int _findLast(int node, int cl, int cr, int tl, int tr, T tv) {
        if(cr <= tl || cl >= tr) return -1;
        push_lazy(node, cr - cl); //almighty push!
        if(F(v[node], tv)) { //good things
            if(isLeaf(node)) return cl;
            int mid = (cl + cr) / 2;
            int right = _findLast(node * 2 + 1, mid, cr, tl, tr, tv);
            if(right != -1) return right;
            return _findLast(node * 2, cl, mid, tl, tr, tv);
        } else {
            return -1;
        }
    }
};

template<typename T>
struct Tree {
    static constexpr T base = 1e9;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

void solve() {
    
    int n, m; cin >> n >> m;
    vector<array<int,3>> a(m);
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<int> pc(m);
    int l = 0, r = 0;

    Lazy<int,int> lazy(n, 0); //crewmate intervals
    Tree<int> tree(n); //impostor tree
    vector<priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>>> pqs(n);
    vector<int> iu(m);

    auto isok = [&](int idx) -> bool {
        int l = a[idx][1] - 1, r = a[idx][2];
        // cout << "is ok idx : " << idx << " l : " << l << " r : " << r << endl;
        if(a[idx][0]) {
            // cout << "lq : " << lazy.query(l, r) << '\n';
            return lazy.query(l, r) == 0;
        } else {
            int nl = 1 + lazy.findLast(0, r, 0), nr = lazy.findFirst(l, n, 0);
            int mr = tree.query(nl, n);
            return mr > nr;
        }
    };

    auto add = [&](int idx) -> void {
        int l = a[idx][1] - 1, r = a[idx][2];
        // cout << "add idx : " << idx << " l : " << l << " r : " << r << endl;

        if(a[idx][0]) {
            iu[idx] = 1;
            pqs[l].push({r, idx});
            tree.update(l, pqs[l].top()[0]);
        } else {
            lazy.update(l, r, 1);
        }
    };

    auto rem = [&](int idx) -> void {
        int l = a[idx][1] - 1, r = a[idx][2];
        // cout << "rem idx : " << idx << " l : " << l << " r : " << r << endl;

        if(a[idx][0]) {
            iu[idx] = 0;
            while(pqs[l].size() && iu[pqs[l].top()[1]] == 0) pqs[l].pop();
            tree.update(l, pqs[l].size() ? pqs[l].top()[0] : tree.base);
        } else {
            lazy.update(l, r, -1);
        }
    };

    //assume things are good at the beginning of each while
    while(l < m) {
        // cout << "l : " << l << " r : " << r << '\n';
        if(r < m) {
            add(r);
            if(isok(r)) {
                // cout << "ok!\n";
                r++;
            } else {
                // cout << "bad\n";
                rem(r);
                rem(l);
                pc[l++] = r;
            }
        } else {
            pc[l++] = r;
        }
    }

    // cout << "pc : " << pc << '\n';

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        cout << (pc[l-1] >= r ? "YES" : "NO") << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}