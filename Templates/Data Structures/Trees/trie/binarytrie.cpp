struct Trie {
    const int depth = 31;
    struct Node {
        array<int,2> a;
        int cnt;
        Node() {
            a = {-1,-1};
            cnt = 0;
        }
    };
    vector<Node> nodes;

    Trie () {
        nodes.push_back(Node());
    }

    void insert(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] == -1) {
                nodes[curr].a[bit] = nodes.size();
                nodes.push_back(Node());
            }
            curr = nodes[curr].a[bit];
            nodes[curr].cnt++;
        }
    }

    int query(int num) {
        int res = 0;
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = (((num >> i) & 1) ^ 1);
            if(nodes[curr].a[bit] != -1 && nodes[nodes[curr].a[bit]].cnt > 0) {
                res += (1 << i);
                curr = nodes[curr].a[bit];
            } else if(nodes[curr].a[bit ^ 1] != -1 && nodes[nodes[curr].a[bit ^ 1]].cnt > 0) {
                curr = nodes[curr].a[bit ^ 1];
            } else {
                return -1;
            }
        }
        return res;
    }

    bool find(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] != -1) {
                curr = nodes[curr].a[bit];
            } else {
                return 0;
            }
        }
        return 1;
    }

    bool erase(int num) {
        if(find(num)) {
            int curr = 0;
            for(int i = depth - 1; i >= 0; i--) {
                curr = nodes[curr].a[((num >> i) & 1)];
                nodes[curr].cnt--;
            }
            return 1;
        } else {
            return 0;
        }
    }
};