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