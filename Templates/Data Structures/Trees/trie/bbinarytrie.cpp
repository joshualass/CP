template <typename T, int MAX_LOG> struct BinaryTrie {
    struct Node {
        std::array<int, 2> nxt;
        int count;
        Node() : nxt{-1, -1}, count(0) {}
    };
 
    std::vector<Node> nodes;
 
    inline int& next(int i, int j) { return nodes[i].nxt[j]; }
 
    BinaryTrie() { nodes.emplace_back(); }
 
    void insert(const T& x) {
        int cur = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = x >> i & 1;
            int nxt = next(cur, f);
            if (nxt == -1) {
                nxt = nodes.size();
                next(cur, f) = nxt;
                nodes.emplace_back();
            }
            nodes[cur].count++;
            cur = nxt;
        }
        nodes[cur].count++;
    }
 
    void erase(const T& x) {
        assert(count(x));
        int cur = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = x >> i & 1;
            nodes[cur].count--;
            cur = next(cur, f);
        }
        nodes[cur].count--;
    }
 
    int find(const T& x) {
        int cur = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = x >> i & 1;
            cur = next(cur, f);
            if (cur == -1) return -1;
        }
        return cur;
    }
 
    int count(const T& x) {
        int idx = find(x);
        return idx == -1 ? 0 : nodes[idx].count;
    }
 
    T min_element(const T& xor_val = 0) {
        int cur = 0;
        T res = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = xor_val >> i & 1;
            int l = next(cur, f), r = next(cur, f ^ 1);
            if (l == -1 or nodes[l].count == 0) {
                cur = r;
                res |= T(f ^ 1) << i;
            } else {
                cur = l;
                res |= T(f) << i;
            }
        }
        return res;
    }
 
    T max_element(const T& xor_val = 0) { return min_element(~xor_val); }
 
    T kth_element(int k, const T& xor_val = 0) const {
        int cur = 0;
        T res = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = xor_val >> i & 1;
            int l = next(cur, f), r = next(cur, f ^ 1);
            if (l == -1 or nodes[l].count <= k) {
                cur = r;
                k -= (l == -1 ? 0 : nodes[l].count);
                res |= T(f ^ 1) << i;
            } else {
                cur = l;
                res |= T(f) << i;
            }
        }
        return res;
    }
 
    int count_less(const T& x, const T& xor_val = 0) {
        int cur = 0;
        int res = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--) {
            int f = xor_val >> i & 1, g = x >> i & 1;
            int l = next(cur, f), r = next(cur, f ^ 1);
            if (f != g and l != -1) res += nodes[l].count;
            cur = next(cur, g);
            if (cur == -1) break;
        }
        return res;
    }
};
 