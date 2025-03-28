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
        v[curr] += val;
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
};

template<typename T>
struct Tree2D {
    static constexpr T base = 0;
    vector<Tree<T>> v;
    int n, m, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree2D(int n = 0, int m = 0, T def = base) {
        this->n = n; //max number of elements
        this->m = m;
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, Tree<T>(m, def));
    }
    void update(int x, int y, T val) { //update 0 indexed, assignment
        assert(x < n && x >= 0 && y >= 0 && y < m);
        int curr = x + size;
        while(curr != 1) {
            v[curr].update(y, val);
            curr /= 2;
        }
        v[curr].update(y, val);
    }
    T query(int l1, int r1, int l2, int r2) {//queries in range [l,r)
        return _query(1,0,size,l1, r1, l2, r2);
    }
    T _query(int idx, int cl1, int cr1, int l1, int r1, int l2, int r2) {
        // cout << "idx : " << idx << " cl1 : " << cl1 << " cr1 : " << cr1 << " l1 : " << l1 << " r1 : " << r1 << " l2 : " << l2 << " r2 : " << r2 << endl;
        if(cr1 <= l1 || cl1 >= r1) return base;
        if(cl1 >= l1 && cr1 <= r1) {
            // cout << "add query 2 val : " << v[idx].query(l2, r2);    
            
            return v[idx].query(l2, r2);
        }
        int mid = (cl1 + cr1) / 2;
        return comb (
            _query(idx * 2, cl1, mid, l1, r1, l2, r2),
            _query(idx * 2 + 1, mid, cr1, l1, r1, l2, r2)
        );
    }
};