#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    ll x, y;
    Node *l, *r;
    ll ss, lazy, id; //subtree size, lazy changes to propagate down, original id of this node
    int toggle; //should we toggle the order of this node's subtree
    //need to have at the very least x and id
    Node(ll x, ll id, ll ss = 1, ll y = rng(), ll lazy = 0, int toggle = 0): x(x), y(y), l(nullptr), r(nullptr), ss(ss), lazy(lazy), id(id), toggle(toggle) {}
};

void push(Node *cur) {
    if(!cur) return;
    cur->x += cur->lazy;
    if(cur->l) cur->l->lazy += cur->lazy;
    if(cur->r) cur->r->lazy += cur->lazy;
    cur->lazy = 0;

    if()

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}
