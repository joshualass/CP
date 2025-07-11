#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<Info> a(n);
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i] = Info(x);
    }

    PTree ptree(a);

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int k, a, x; cin >> k >> a >> x;
            k--; a--;
            ptree.update(k, a, Info(x));
        } else if(t == 2) {
            int k, a, b; cin >> k >> a >> b;
            k--, a--;
            cout << ptree.query(k, a, b).v << '\n';
        } else {
            int k; cin >> k;
            k--;
            ptree.copy(k);
        }
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
 
// struct Node {
//     Node *l, *r;
//     ll s;
//     Node(ll s): s(s), l(nullptr), r(nullptr) {}
//     Node(ll s, Node *l, Node *r): s(s), l(l), r(r) {}
// };
 
// Node* build(vector<ll> &a, int cl, int cr) {
//     if(cl + 1 == cr) return new Node(a[cl]);
//     int mid = (cl + cr) / 2;
//     Node* l = build(a, cl, mid), *r = build(a, mid, cr);
//     return new Node(l->s + r->s, l, r);
// }
 
// Node* update(Node* cur, int cl, int cr, int idx, ll val) {
//     if(idx < cl || idx >= cr) return cur;
//     if(cl + 1 == cr) {
//         return new Node(val);
//     }
//     int mid = (cl + cr) / 2;
//     Node* l = update(cur->l, cl, mid, idx, val), *r = update(cur->r, mid, cr, idx, val);
//     return new Node(l->s + r->s, l, r);
// }
 
// ll query(Node* cur, int tl, int tr, int cl, int cr) {
//     if(cr <= tl || tr <= cl) return 0;
//     if(tl <= cl && cr <= tr) return cur->s;
//     int mid = (cl + cr) / 2;
//     return query(cur->l, tl, tr, cl, mid) + query(cur->r, tl, tr, mid, cr);
// }
 
// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
 
//     int n, q; cin >> n >> q;
//     vector<ll> b(n);
//     for(ll &x : b) cin >> x;
 
//     vector<Node*> roots;
//     vector<int> rootidx;
 
//     roots.push_back(build(b, 0, n));
//     rootidx.push_back(0);
 
//     for(int i = 0; i < q; i++) {
//         int t; cin >> t;
//         if(t == 1) {
//             int k, a, x; cin >> k >> a >> x;
//             a--, k--;
//             roots.push_back(update(roots[rootidx[k]], 0, n, a, x));
//             assert(k < rootidx.size());
//             rootidx[k] = roots.size() - 1;
//         } else if(t == 2) {
//             int k, a, b; cin >> k >> a >> b;
//             k--, a--;
//             assert(k < rootidx.size());
//             assert(rootidx[k] < roots.size());
//             cout << query(roots[rootidx[k]], a, b, 0, n) << '\n';
//         } else if(t == 3) {
//             int k; cin >> k;
//             k--;
//             assert(k < rootidx.size());
//             rootidx.push_back(rootidx[k]);
//         }
//     }
 
//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// //this version is correct, but it TLEs!
// /*
// struct Node {
//     Node *l, *r;
//     ll s;
//     Node(ll s): s(s), l(nullptr), r(nullptr) {}
//     Node(ll s, Node *l, Node *r): s(s), l(l), r(r) {}
// };

// Node* build(vector<ll> &a, int cl, int cr) {
//     if(cl + 1 == cr) return new Node(a[cl]);
//     int mid = (cl + cr) / 2;
//     Node* l = build(a, cl, mid), *r = build(a, mid, cr);
//     return new Node(l->s + r->s, l, r);
// }

// Node* update(Node* cur, int cl, int cr, int idx, ll val) {
//     // cout << "update cl : " << cl << " cr : " << cr << " idx : " << idx << " val : " << val << endl;
//     // cout << "value here : " << cur->s << endl;
//     if(idx < cl || idx >= cr) return cur;
//     if(cl + 1 == cr) {
//         return new Node(val);
//     }
//     int mid = (cl + cr) / 2;
//     Node* l = update(cur->l, cl, mid, idx, val), *r = update(cur->r, mid, cr, idx, val);
//     return new Node(l->s + r->s, l, r);
// }

// ll query(Node* cur, int tl, int tr, int cl, int cr) {
//     // cout << "tl : " << tl << " tr : " << tr << " cl : " << cl << " cr : " << cr << endl;
//     // cout << "value here : " << cur->s << endl;
//     if(cr <= tl || tr <= cl) return 0;
//     if(tl <= cl && cr <= tr) return cur->s;
//     int mid = (cl + cr) / 2;
//     return query(cur->l, tl, tr, cl, mid) + query(cur->r, tl, tr, mid, cr);
// }
// */

// // struct Node {
// //     int l, r;
// //     ll s;
// //     Node(ll s): s(s), l(-1), r(-1) {}
// //     Node(ll s, int l, int r): s(s), l(l), r(r) {}
// // };

// // vector<Node> nodes;

// // int build(vector<ll> &a, int cl, int cr) {
// //     if(cl + 1 == cr) {
// //         nodes.push_back(Node(a[cl]));
// //         return nodes.size() - 1;    
// //     }
// //     int mid = (cl + cr) / 2;
// //     int l = build(a, cl, mid), r = build(a, mid, cr);
// //     nodes.push_back(Node(nodes[l].s + nodes[r].s, l, r));
// //     return nodes.size() - 1;
// // }

// // int update(int cur, int cl, int cr, int idx, ll val) {
// //     // cout << "update cl : " << cl << " cr : " << cr << " idx : " << idx << " val : " << val << endl;
// //     // cout << "value here : " << cur->s << endl;
// //     if(idx < cl || idx >= cr) return cur;
// //     if(cl + 1 == cr) {
// //         nodes.push_back(Node(val));
// //         return nodes.size() - 1;
// //     }
// //     int mid = (cl + cr) / 2;
// //     int l = update(nodes[cur].l, cl, mid, idx, val), r = update(nodes[cur].r, mid, cr, idx, val);
// //     nodes.push_back(Node(nodes[l].s + nodes[r].s, l, r));
// //     return nodes.size() - 1;
// // }

// // ll query(int cur, int tl, int tr, int cl, int cr) {
// //     // cout << "tl : " << tl << " tr : " << tr << " cl : " << cl << " cr : " << cr << endl;
// //     // cout << "value here : " << cur->s << endl;
// //     if(cr <= tl || tr <= cl) return 0;
// //     if(tl <= cl && cr <= tr) return nodes[cur].s;
// //     int mid = (cl + cr) / 2;
// //     return query(nodes[cur].l, tl, tr, cl, mid) + query(nodes[cur].r, tl, tr, mid, cr);
// // }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q; cin >> n >> q;
//     vector<ll> b(n);
//     for(ll &x : b) cin >> x;

//     vector<int> roots;
//     vector<int> rootidx;

//     roots.push_back(build(b, 0, n));
//     rootidx.push_back(0);

//     for(int i = 0; i < q; i++) {
//         int t; cin >> t;
//         if(t == 1) {
//             int k, a, x; cin >> k >> a >> x;
//             a--, k--;
//             roots.push_back(update(roots[rootidx[k]], 0, n, a, x));
//             assert(k < rootidx.size());
//             rootidx[k] = roots.size() - 1;
//         } else if(t == 2) {
//             int k, a, b; cin >> k >> a >> b;
//             k--, a--;
//             assert(k < rootidx.size());
//             assert(rootidx[k] < roots.size());
//             cout << query(roots[rootidx[k]], a, b, 0, n) << '\n';
//         } else if(t == 3) {
//             int k; cin >> k;
//             k--;
//             assert(k < rootidx.size());
//             rootidx.push_back(rootidx[k]);
//         }
//     }

//     return 0;
// }

// /*
// 5 6
// 2 3 1 2 5
// 3 1
// 2 1 1 5
// 2 2 1 5
// 1 2 2 5
// 2 1 1 5
// 2 2 1 5

// 5 2
// 2 3 1 2 5
// 3 1
// 2 1 1 5
// 2 2 1 5

// */