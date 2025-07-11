template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
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
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return !(tree_node[0] >= query_val[0] && tree_node[1] <= query_val[1]);
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
    pair<int,T> find_last(int l, int r, T query_val) {
        return _find_last(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
            if(p.first != -1) {
                return p;
            }
            return _find_last(idx * 2, cl, mid, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
    bool cond_range(T query_val, T cur) {
        return cur >= query_val;
    }
    int find_first_range(int l, int r, T query_val) {
        T cur = base;
        return _find_first_range(1, 0, size, l, r, query_val, cur);
    }
    int _find_first_range(int idx, int cl, int cr, int tl, int tr, T qv, T &cur) {
        if(cr <= tl || cl >= tr) return -1; //no overlap here, cya
        if(isLeaf(idx)) {
            if(cond_range(qv, cur)) return -1; //already done, do not add more
            cur = comb(cur, v[idx]);
            if(cond_range(qv, cur)) { //done now, this is the earliest
                return idx - size;
            } else { //not done, more work to do
                return -1;
            }
        }
        if(cl >= tl && cr <= tr) { //complete overlap, have this so that the complexity of this algorithm is truly logn
            if(!cond_range(qv, comb(cur, v[idx]))) { //still bad, do not go down
                cur = comb(cur, v[idx]);
                return -1;
            }
        }
        int mid = (cl + cr) / 2;
        int try_left = _find_first_range(idx * 2, cl, mid, tl, tr, qv, cur);
        if(try_left != -1) return try_left;
        return _find_first_range(idx * 2 + 1, mid, cr, tl, tr, qv, cur);
    }
};

/*
general find first logic
just like a query, make sure there is some overlap
then see if there is anything good in interval to keep pursuing
if so, see if done if leaf else, try the greedy sides. 
*/

//TODO check that range properly works with tl and tr. only tested for tl = 0 and tr = n. 