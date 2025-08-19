#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    ll x, y;
    Node *l, *r;
    ll v;
    ll id;
    Node(ll x, ll v, ll id): x(x), y(rng()), l(nullptr), r(nullptr), v(v), id(id) {}
    // Node(ll x, ll y): x(x), y(y), l(nullptr), r(nullptr) {}
};

void dfs(Node *cur) {
    if(cur == nullptr) return;
    cout << "cur x : " << cur->x << " cur y : " << cur->y << '\n';
    if(cur->l) {
        cout << "has left child with x : " << cur->l->x << " y : " << cur->l->y << '\n';
    }
    if(cur->r) {
        cout << "has right child with x : " << cur->r->x << " y : " << cur->r->y << '\n';
    }
    dfs(cur->l);
    dfs(cur->r);
}

void test_dfs(Node *root) {
    cout << "testing dfs!\n";
    dfs(root);
}

void push(Node *cur) {
    cur->x += cur->v;
    if(cur->l) cur->l->v += cur->v;
    if(cur->r) cur->r->v += cur->v;
    cur->v = 0;
}

void res_dfs(Node* cur, string &res, string &s) {
    if(!cur) return;
    push(cur);
    res_dfs(cur->l, res, s);
    res.push_back(s[cur->id]);
    res_dfs(cur->r, res, s);
}

void inorder_dfs(Node *cur) {
    if(!cur) return;
    push(cur);
    inorder_dfs(cur->l);
    cout << "x : " << cur->x << '\n';
    inorder_dfs(cur->r);
}

//partitions treap into L with keys <= x and R with keys > x. 
array<Node*, 2> split(Node *cur, ll x) {
    if(cur == nullptr) return {nullptr, nullptr};
    push(cur);
    if(cur->x <= x) {
        auto [cl, cr] = split(cur->r, x);
        cur->r = cl;
        return {cur, cr};
    } else {
        auto [cl, cr] = split(cur->l, x);
        cur->l = cr;
        return {cl, cur};
    }
}

Node* merge(Node *tl, Node *tr) {
    if(tl) push(tl);
    if(tr) push(tr);
    if(tl == nullptr) {
        // cout << "itachi0\n";
        return tr;
    }
    if(tr == nullptr) {
        // cout << "itachi1\n";
        return tl;
    }
    if(tl->y >= tr->y) {
        if(tl->r != nullptr && tl->r->y >= tr->y) {
            merge(tl->r, tr);
        } else {
            merge(tl->r, tr);
            tl->r = tr;
        }
        return tl;
    } else {
        if(tr->l != nullptr && tr->l->y >= tl->y) {
            merge(tl, tr->l);
        } else {
            merge(tl, tr->l);
            tr->l = tl;
        }
        return tr;
    }
}

Node* insert(Node *root, Node *add) {
    auto [tl, tr] = split(root, add->x);
    tl = merge(tl, add);
    // cout << "tl\n";
    // test_dfs(tl);
    // cout << "test tl again\n";
    // test_dfs(tl);
    // cout << "tr\n";
    // test_dfs(tr);
    return merge(tl, tr);
}

Node* erase(Node *root, ll key) {
    auto [tl, tr] = split(root, key);
    auto [ttl, ttr] = split(tl, key - 1);
    return merge(ttl, tr);
}

Node* op(Node *root, int l, int r, int n) {

    // cout << "l : " << l << " r : " << r << " n : " << n << '\n';
    // cout << "test root" << endl;
    // test_dfs(root);

    // cout << "PRE OP INORDER DFS" << endl;
    // inorder_dfs(root);

    auto [ln, mrn] = split(root, l - 2);
    // array<Node*, 2> res0 = split(root, l - 2);
    // Node *ln = res0[0], *mrn = res0[1];

    // cout << "test ln" << endl;;
    // test_dfs(ln);
    // cout << "test mrn" << endl;
    // test_dfs(mrn);
    auto [mn, rn] = split(mrn, r - 1);
    // cout << "test mn" << endl;
    // test_dfs(mn);
    // cout << "test rn" << endl;
    // test_dfs(rn);

    if(mn) {
        mn->v += n - r;
    }
    if(rn) {
        rn->v -= r - l + 1;
    }

    root = merge(ln, rn);
    // cout << "POST OP PARTIAL ROOT INORDER DFS" << endl;
    // inorder_dfs(root);

    root = merge(root, mn);
    // cout << "POST OP INORDER DFS" << endl;
    // inorder_dfs(root);

    return root;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Node *root = nullptr;
    // for(int i = 0; i < 10; i++) {
    //     root = merge(root, new Node(i, 0));
    // }

    // test_dfs(root);

    // cout << "erase root x of : " << root->x << '\n';

    // root = erase(root, root->x);

    // test_dfs(root);

    int n, m; cin >> n >> m;
    string s; cin >> s;
    Node* root = nullptr;
    for(int i = 0; i < n; i++) {
        root = insert(root, new Node(i, 0, i));
    }

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        root = op(root, l, r, n);
    }

    string res = "";
    res_dfs(root, res, s);
    cout << res << '\n';

    return 0;
}
