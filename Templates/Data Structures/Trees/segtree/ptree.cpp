struct Info {
    ll v;
    Info(): v(0) {}
    Info(ll v): v(v) {}
};

Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.v = lhs.v + rhs.v;
    return res;
}

struct PTree {
    struct Node {
        int l, r;
        Info info;
        Node(Info info): info(info), l(-1), r(-1) {}
        Node(Info info, int l, int r): info(info), l(l), r(r) {}
    };

    int n;
    vector<Node> data;
    vector<int> roots;

    PTree() {}
    PTree(vector<Info> &a) {
        build(a);
    }
    void build(vector<Info> &a) {
        n = a.size();
        roots.push_back(build(a, 0, n));
    }

    void update(int k, int i, Info info) {
        assert(k < roots.size());
        roots[k] = update(roots[k], 0, n, i, info);
    }

    Info query(int k, int tl, int tr) {
        assert(k < roots.size());
        return query(roots[k], tl, tr, 0, n);
    }

    int copy(int k) {
        roots.push_back(roots[k]);
        return roots.size() - 1;
    }

private:
    int build(vector<Info> &a, int cl, int cr) {
        if(cl + 1 == cr) {
            data.push_back(Node(a[cl]));
            return data.size() - 1;
        }
        int mid = (cl + cr) / 2;
        int l = build(a, cl, mid), r = build(a, mid, cr);
        data.push_back(Node(data[l].info + data[r].info, l, r));
        return data.size() - 1;
    }

    int update(int cur, int cl, int cr, int idx, Info info) {
        if(idx < cl || idx >= cr) return cur;
        if(cl + 1 == cr) {
            data.push_back(Node(info));
            return data.size() - 1;
        }
        int mid = (cl + cr) / 2;
        int l = update(data[cur].l, cl, mid, idx, info), r = update(data[cur].r, mid, cr, idx, info);
        data.push_back(Node(data[l].info + data[r].info, l, r));
        return data.size() - 1;
    }

    Info query(int cur, int tl, int tr, int cl, int cr) {
        if(cr <= tl || tr <= cl) return Info();
        if(tl <= cl && cr <= tr) return data[cur].info;
        int mid = (cl + cr) / 2;
        return query(data[cur].l, tl, tr, cl, mid) + query(data[cur].r, tl, tr, mid, cr);
    }

};