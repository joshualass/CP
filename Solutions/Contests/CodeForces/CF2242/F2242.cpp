#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int maxn = 1e1;

struct node {
    int x, delta, v, size;
    node *l, *r;
    node(int x, int delta, int v, node *l, node *r): x(x), delta(delta), v(v), l(l), r(r), size(1) {}
};

ostream& operator<<(ostream& os, node *cur) {
    os << "x : " << cur->x << " d : " << cur->delta << " v : " << cur->v;
    return os;
}

node* push(node* x, int d = 0) {
    assert(x);
    x->delta += d;
    if(x->l) x->l->delta += x->delta;
    if(x->r) x->r->delta += x->delta;
    x->x += x->delta;
    return new node(x->x, 0, x->v, x->l, x->r);
}

void pull(node* x) {
    assert(x);
    x->size = 1 + (x->l ? x->l->size : 0) + (x->r ? x->r->size : 0);
}

array<node*, 2> split(node* cur, int x) {
    if(!cur) return {nullptr, nullptr};
    cur = push(cur);
    // cout << "split cur : " << cur << endl;
    array<node*,2> res = {};
    if(cur->x >= x) {
        auto [l, r] = split(cur->l, x);
        cur->l = r;
        pull(cur);
        res = {l, cur};
    } else {
        auto [l, r] = split(cur->r, x);
        cur->r = l;
        pull(cur);
        res = {cur, r};
    }
    return res;
}

node* merge(node* l, node* r) {
    if(!l && !r) return nullptr;
    if(!l) return r;
    if(!r) return l;
    l = push(l);
    r = push(r);
    if(rng() % (l->size + r->size) < l->size) {
        auto c = merge(l->r, r);
        l->r = c;
        pull(l);
        return l;
    } else {
        auto c = merge(l, r->l);
        r->l = c;
        pull(r);
        return r;
    }
}

int query(node *cur, int t) {
    assert(cur);
    cur = push(cur);
    cout << "query t : " << t << " cur : " << cur << endl;
    if(cur->x == t) return cur->v;
    if(cur->x > t) {
        assert(cur->l);
        return query(cur->l, t);
    } else {
        assert(cur->r);
        return query(cur->r, t);
    }
}

void print(node* cur) {
    if(cur) {
        cur = push(cur);
        print(cur->l);
        cout << cur << endl;
        print(cur->r);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    node* root = nullptr;
    for(int i = 0; i < 2 * maxn; i++) {
        root = merge(root, new node(i, 0, i, nullptr, nullptr));
    }

    // cout << root << endl;

    auto print_tree = [&](node* cur, int mx = 20) -> void {
        // for(int i = 0; i < mx; i++) {
        //     cout << "i : " << i << " q : ";
        //     cout.flush();
        //     cout << query(root, i) << " ";
        // }
        // cout << endl;
        print(cur);
    };

    print_tree(root);

    for(int i = n - 1; i >= 0; i--) {
        cout << "i : " << i << endl;
        auto [l, m] = split(root, a[i]);

        cout << "l : " << endl;
        print_tree(l, a[i]);

        auto [rl, rr] = split(m, a[i] * 2);

        node* nl = push(rl, -a[i]);
        node *nr = push(root, a[i]);
        root = merge(nl, nr);

        cout << "nl : " << endl;
        print_tree(nl, a[i]);

        cout << "nr : " << endl;
        print_tree(nr);

        cout << "after i : " << i << endl;
        print_tree(root);
        cout << query(root, 0) << " \n"[i == 0];
    }

    return 0;
}
