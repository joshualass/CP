#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Info {
    int v;
    Info(): v(INT_MAX) {}
    Info(int v): v(v) {}
};

// void merge(Info &lhs, Info &rhs, Info &res) {
//     res.v = min(lhs.v, rhs.v);
// }

// Info operator+(const Info &lhs, const Info &rhs) {
//     // Info res;
//     // res.v = min(lhs.v, rhs.v);
//     // return res;
//     return Info(min(lhs.v, rhs.v));
// }

struct PTree {
    struct Node {
        int l, r;
        // Info info;
        int v;
        Node(): v(INT_MAX), l(-1), r(-1) {}
        Node(int v): v(v), l(-1), r(-1) {}
        Node(int v, int l, int r): v(v), l(l), r(r) {}
    };
    
    void merge(Node &lhs, Node &rhs, Node &res) {
        res.v = min(lhs.v, rhs.v);
    }

    int n, dp, rp;
    vector<Node> data;
    vector<int> roots;

    PTree() {}
    PTree(vector<int> &a) {
        build(a);
    }

    void build(vector<int> &a) {
        n = a.size();
        dp = 0;
        rp = 0;
        data.resize(n * 22);
        roots.resize(n + 1);
        roots[rp++] = 0;
        data[0] = Node(INT_MAX, 0, 0);
        dp++;
        // roots[rp++] = build(a, 0, n);
    }

    void update(int k, int i, int info) {
        assert(k < roots.size());
        roots[k] = update(roots[k], 0, n, i, info);
    }

    int query(int k, int tl, int tr) {
        assert(k < roots.size());
        int res = INT_MAX;
        query(roots[k], tl, tr, 0, n, res);
        return res;
    }

    int copy(int k) {
        roots[rp] = roots[k];
        return rp++;
    }

private:
    // int build(vector<int> &a, int cl, int cr) {
    //     if(cl + 1 == cr) {
    //         data[dp].v = a[cl];
    //         return dp++;
    //     }
    //     int mid = (cl + cr) / 2;
    //     int l = build(a, cl, mid), r = build(a, mid, cr);
    //     // data[dp] = Node(data[l].info + data[r].info, l, r);
    //     data[dp].l = l;
    //     data[dp].r = r;
    //     merge(data[l], data[r], data[dp]);
    //     return dp++;
    // }

    int update(int cur, int cl, int cr, int idx, int &info) {
        if(idx < cl || idx >= cr) return cur;
        if(cl + 1 == cr) {
            data[dp].v = info;
            return dp++;
        }
        int mid = (cl + cr) / 2;
        if(idx < mid) {
            int upd_idx = update(data[cur].l, cl, mid, idx, info);
            // data[dp] = Node(data[upd_idx].info + data[data[cur].r].info, upd_idx, data[cur].r);
            data[dp].l = upd_idx;
            data[dp].r = data[cur].r;
        } else {
            int upd_idx = update(data[cur].r, mid, cr, idx, info);
            // data[dp] = Node(data[data[cur].l].info + data[upd_idx].info, data[cur].l, upd_idx);
            data[dp].l = data[cur].l;
            data[dp].r = upd_idx;
        }
        merge(data[data[dp].l], data[data[dp].r], data[dp]);
        // int l = update(data[cur].l, cl, mid, idx, info), r = update(data[cur].r, mid, cr, idx, info);
        // data[dp] = Node(data[l].info + data[r].info, l, r);
        return dp++;
    }

    void query(int cur, int tl, int tr, int cl, int cr, int &res) {
        if(cr <= tl || tr <= cl || !cur) return;
        if(tl <= cl && cr <= tr) {
            res = min(res, data[cur].v);
            return;
        }
        int mid = (cl + cr) / 2;
        query(data[cur].l, tl, tr, cl, mid, res);
        query(data[cur].r, tl, tr, mid, cr, res);
    }

};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> b(n, INT_MAX);
    PTree ptree(b);

    map<int,int> pi;
    for(int i = 0; i < n; i++) {
        if(pi.count(a[i])) {
            int j = pi[a[i]];
            ptree.update(i, j, i - j);
        }
        ptree.copy(i);
        pi[a[i]] = i;
    }

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--;
        int res = ptree.query(r - 1, l, r);
        cout << (res == INT_MAX ? -1 : res) << '\n';
    }

    return 0;
}
