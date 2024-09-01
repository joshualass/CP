template<typename T>
struct sparse {

    vector<vector<T>> sparsetable;
    int n, d;

    sparse() {}

    sparse(vector<T> a) {
        buildTable(a);
    }

    T op(T a, T b) {
        return min(a,b);
    }

    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));

        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }

    }

    //[l,r) always. 
    T query(int l, int r) {
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }

};