#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    int val, rev, size;
    ll sum;
    ll y;
    Node(int val): l(nullptr), r(nullptr), val(val), rev(0), size(1), sum(val), y(rng()) {}
};

void push(Node *cur) {
    assert(cur);
    if(cur->rev) {
        swap(cur->l, cur->r);
        if(cur->l) cur->l->rev ^= 1;
        if(cur->r) cur->r->rev ^= 1;
        cur->rev = 0;
    }
}

//update size + sum
void update(Node *cur) {
    assert(cur);
    cur->size = 1 + (cur->l ? cur->l->size : 0) + (cur->r ? cur->r->size : 0);
    cur->sum = cur->val + (cur->l ? cur->l->sum : 0LL) + (cur->r ? cur->r->sum : 0LL);
}

array<Node*, 2> split(Node *cur, int nl) {
    if(!cur) return {nullptr, nullptr};
    push(cur);
    int cls = (cur->l ? cur->l->size : 0);
    array<Node*, 2> res;
    if(cls + 1 <= nl) { //keep left stuff
        array<Node*, 2> rhs = split(cur->r, nl - (cls + 1));
        cur->r = rhs[0];
        res = {cur, rhs[1]};
    } else {
        array<Node*, 2> lhs = split(cur->l, nl);
        cur->l = lhs[1];
        res = {lhs[0], cur};
    }

    update(cur);
    return res;
}

Node* merge(Node *lhs, Node *rhs) {
    if(!lhs && !rhs) return nullptr;
    if(!lhs) return rhs;
    if(!rhs) return lhs;

    push(lhs);
    push(rhs);

    Node *res;
    if(lhs->y > rhs->y) {
        lhs->r = merge(lhs->r, rhs);
        res = lhs;
    } else {
        rhs->l = merge(lhs, rhs->l);
        res = rhs;
    }

    update(res);
    // cout << "update called on res with val : " << res->val << " updated sum : " << res->sum << endl;
    // if(res->l) {
    //     cout << "yikes bro lsum : " << res->l->sum << endl;
    // }
    // if(res->r) {
    //     cout << "yikes bro rsum : " << res->r->sum << endl;
    // }

    return res;
}

void dfs(Node *cur) {
    if(!cur) return;
    dfs(cur->l);
    cout << "cur : " << cur->y << " val : " << cur->val << " size : " << cur->size << " sum : " << cur->sum << endl;
    // if(cur->l) {
    //     cout << "has lc with sum : " << cur->l->sum << endl;
    // }
    // if(cur->r) {
    //     cout << "has rc with sum : " << cur->r->sum << endl;
    // }
    dfs(cur->r);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    int start; cin >> start;
    Node *root = new Node(start);

    // cout << "start\n";
    // dfs(root);

    for(int i = 1; i < n; i++) {
        // cout << "i\n";
        int x; cin >> x;
        Node *nx = new Node(x);
        root = merge(root, nx);
        // dfs(root);
    }

    // dfs(root);

    for(int i = 0; i < m; i++) {
        int t, a, b; cin >> t >> a >> b;
        auto [l, mr] = split(root, a - 1);
        auto [m, r] = split(mr, b - a + 1);
        assert(m);
        // cout << "l" << endl;
        // dfs(l);
        // cout << "m" << endl;
        // dfs(m);
        // cout << "r" << endl;
        // dfs(r);
        if(t == 1) {
            m->rev ^= 1;
        } else {
            cout << m->sum << '\n';
        }
        auto lm = merge(l, m);
        root = merge(lm, r);
    }

    return 0;
}
