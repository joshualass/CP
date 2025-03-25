template<typename T>
struct Tree {
    static constexpr T base = -1;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
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
        return tree_node >= query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != -1){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
};