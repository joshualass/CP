//supports 2 operations
// 1 - update range of elements with f()
// 2 - query for a single element
struct Tree {
    typedef ll T; //update the data type, currently int. often update to ll
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    Tree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void set(int pos, T val) {
        s[pos + n] = val;
    }
    void update(int l, int r, T u) { //increases values in [l,r) by u
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                s[l] = f(s[l],u);
                l++;
            }
            if(r & 1) {
                r--;
                s[r] = f(s[r],u);
            }
        }
    }
    T query(int pos) { //queries the value of element at pos
        T ans = s[pos += n];
        while(pos /= 2) {
            ans = f(ans,s[pos]);
        }
        return ans;
    }
};