//homemade treap template - could be better

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    ll x, y;
    Node *l, *r;
    ll v;
    Node(ll x, ll v): x(x), y(rng()), l(nullptr), r(nullptr), v(v) {}
    // Node(ll x, ll y): x(x), y(y), l(nullptr), r(nullptr) {}
};

//partitions treap into L with keys <= x and R with keys > x. 
array<Node*, 2> split(Node *cur, ll x) {
    if(cur == nullptr) return {nullptr, nullptr};
    
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
    if(tl == nullptr) {
        return tr;
    }
    if(tr == nullptr) {
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
    return merge(tl, tr);
}

Node* erase(Node *root, ll key) {
    auto [tl, tr] = split(root, key);
    auto [ttl, ttr] = split(tl, key - 1);
    return merge(ttl, tr);
}

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