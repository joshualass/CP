const int d = 30;
struct B {

    int sz = 0;
    array<int,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    B operator+(const B& other) const {
        B res;
        res.basis = this->basis;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(other.basis[bit]) res.insert(other.basis[bit]);
        }
        return res;
    }

    bool insert(int x) { //returns true if insert was successful
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    sz++;
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    return 0;
                }
            }
        }
        return 1;
    }

    int query() {
        int res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }

    int order(int x) { //finds the order that x has in the basis. 
        //check that x is in this basis
        assert(find(x));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if((x >> bit) & 1) {
                    res += 1 << idx;
                }
                idx--;
            }
        }
        return res;
    }

    int get(int order) { //given order, find the value in this basis. 
        assert(order < (1 << sz));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if(((order >> idx) & 1) != ((res >> bit) & 1)) {
                    res ^= basis[bit];
                }
                idx--;
            }
        }
        return res;
    }
};