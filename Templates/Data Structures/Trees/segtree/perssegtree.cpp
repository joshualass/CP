template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<vector<pair<int,T>>> v;
    int n, size, op;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        op = 0;
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {{-1, 0}});
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].push_back({op,val});
        while(curr != 1) {
            if(curr & 1) {
                v[curr / 2].push_back({op, comb(v[curr ^ 1].back().second, v[curr].back().second)});
            } else {
                v[curr / 2].push_back({op, comb(v[curr].back().second, v[curr ^ 1].back().second)});
            }
            curr /= 2;
        }
        op++;
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r, int time) {//queries in range [l,r)
        return _query(1,0,size,l,r,time);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr, int &time) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) {
            int l = 0, r = v[idx].size() - 1;
            while(l != r) {
                int m = (l + r + 1) / 2;
                if(v[idx][m].first <= time) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            return v[idx][l].second;
        }
        
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr, time),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, time)
        );
    }
};