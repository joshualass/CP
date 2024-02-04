template<typename T>
struct Lazy {
    static constexpr T ln = 0, qn = 0; //stores the starting values at all nodes, 
    vector<T> v;      //stores values at each index we are querying for
    vector<T> lazy;   //stores lazy updates at each node
    vector<bool> upd; //stores at each node, whether there is a lazy update to push
    int n, size;

    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = ln) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
        upd.assign(size * 2, 0);
    }
    bool isLeaf(int node) {
        return node >= size;
    }
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, T val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] = lazy[node] + val; 
        upd[node] = 1;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node] * size;
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
            upd[node * 2] = 1;
            upd[node * 2 + 1] = 1;
        }
        lazy[node] = ln;
        upd[node] = 0;
    }
    void update(int l, int r, T val) {
        _update(1,0,size,l,r,val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, T &val) {
        if(upd[node]) {
            push_lazy(node,currr-currl);
        }
        if (currl >= targetr || currr <= targetl) { //there is no overlap
            return; //do nothing if there is no overlap
        }
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
            push_lazy(node, currr-currl);
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) {
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) { //no overlap
            return qn; 
        } 
        if(upd[node]) push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
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