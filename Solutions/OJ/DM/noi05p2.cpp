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

/*
good treap practice, 86/100, tleing on one testcase and tl is quite tight ...

when doing lazy operations, it is very important to 
*/
const int an = 1e9 + 5;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    ll y;
    int val, size, sum, rev, assign; 
    int lmax, rmax, smax;

    Node(int val): l(nullptr), r(nullptr), y(rng()), val(val), size(1), sum(val), rev(0), assign(an), lmax(max(0,val)), rmax(max(0,val)), smax(max(0, val)) {}

};

void push(Node *cur) {
    // assert(cur);
    if(cur->rev) {
        cur->rev = 0;
        if(cur->l) {
            cur->l->rev ^= 1;
        }
        if(cur->r) {
            cur->r->rev ^= 1;
        }
        swap(cur->l, cur->r);
        swap(cur->lmax, cur->rmax);
    }
    if(cur->assign != an) {
        if(cur->l) cur->l->assign = cur->assign;
        if(cur->r) cur->r->assign = cur->assign;
        cur->val = cur->assign;
        cur->sum = cur->size * cur->assign;
        cur->lmax = max(0, cur->sum);
        cur->rmax = max(0, cur->sum);
        cur->smax = max(0, cur->sum);
        cur->assign = an;
    }
}

void pull(Node *cur) {
    // assert(cur);
    // assert(cur->rev == 0);
    // assert(cur->assign == an);

    if(cur->l) push(cur->l);
    if(cur->r) push(cur->r);
    
    cur->size = 1 + (cur->l ? cur->l->size : 0) + (cur->r ? cur->r->size : 0);
    cur->sum = cur->val + (cur->l ? cur->l->sum : 0) + (cur->r ? cur->r->sum : 0);

    //try ending at all three points
    cur->lmax = max(0, cur->l ? cur->l->lmax : 0);
    cur->lmax = max(cur->lmax, (cur->l ? cur->l->sum : 0) + cur->val);
    cur->lmax = max(cur->lmax, (cur->l ? cur->l->sum : 0) + cur->val + (cur->r ? cur->r->lmax : 0));

    //same thing for the right
    cur->rmax = max(0, cur->r ? cur->r->rmax : 0);
    cur->rmax = max(cur->rmax, (cur->r ? cur->r->sum : 0) + cur->val);
    cur->rmax = max(cur->rmax, (cur->r ? cur->r->sum : 0) + cur->val + (cur->l ? cur->l->rmax : 0));

    //update the best answer
    cur->smax = max(0, cur->l ? cur->l->smax : 0);
    cur->smax = max(cur->smax, cur->r ? cur->r->smax : 0);
    cur->smax = max(cur->smax, (cur->l ? cur->l->rmax : 0) + cur->val + (cur->r ? cur->r->lmax : 0));
}

array<Node*, 2> split(Node* cur, int lsize) {
    if(cur) push(cur);
    if(!cur) return {nullptr, nullptr};

    int curr_lsize = (cur->l ? cur->l->size : 0);
    array<Node*, 2> res;
    // cout << "node stats size : " << cur->size << " l size : " << (cur->l ? cur->l->size : 0) << " r size : " << (cur->r ? cur->r->size : 0) << endl;
    // cout << "lsize : " << lsize << endl;
    // cout << "curr lsize : " << curr_lsize << endl;
    if(curr_lsize >= lsize) {
        // cout << "do not include root into left partition" << endl;
        auto [lhs, rhs] = split(cur->l, lsize);
        cur->l = rhs;
        res = {lhs, cur};
    } else {
        // cout << "include root into left partition\n";
        auto [lhs, rhs] = split(cur->r, lsize - (curr_lsize + 1));
        cur->r = lhs;
        res = {cur, rhs};
    }
    pull(cur);
    return res;
}

//push if it is not null. 
Node* merge(Node *lhs, Node *rhs) {
    if(lhs) push(lhs);
    if(rhs) push(rhs);

    // if(!lhs && !rhs) return nullptr;
    if(!lhs) return rhs;
    if(!rhs) return lhs;

    Node* res;
    if(lhs->y > rhs->y) {//make lhs the root. 
        Node* ch = merge(lhs->r, rhs);
        lhs->r = ch;
        res = lhs;
    } else {
        Node* ch = merge(lhs, rhs->l);
        rhs->l = ch;
        res = rhs;
    }
    pull(res);
    return res;
}

void del(Node *cur) {
    if(!cur) return;
    del(cur->l);
    del(cur->r);
    delete cur;
}

void printTree(Node* cur) {
    if(!cur) return;
    cout << "size : " << cur->size << " sum : " << cur->sum << " lsize : " << (cur->l ? cur->l->size : 0) << " rsize : " << (cur->r ? cur->r->size : 0) << " rev : " << cur->rev << " an : " << cur->assign << endl;
    printTree(cur->l);
    printTree(cur->r);
}

void inOrder(Node *cur) {
    if(!cur) return;
    // push(cur);
    inOrder(cur->l);
    cout << "cur val : " << cur->val << endl;
    inOrder(cur->r);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    Node* root = nullptr;

    vector<int> a;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        // cout << "x : " << x << endl;
        Node* add = new Node(x);
        root = merge(root, add);
        a.push_back(x);
    }

    // cout << "starting tree status" << endl;
    // printTree(root);

    // cout << "start io" << endl;
    // inOrder(root);

    for(int qq = 0; qq < q; qq++) {
        string op; cin >> op;
        if(op == "INSERT") {
            int pos, tot; cin >> pos >> tot;
            // pos--;
            Node* insert_tree = nullptr;
            for(int i = 0; i < tot; i++) {
                int x; cin >> x;
                Node* add = new Node(x);
                insert_tree = merge(insert_tree, add);
                // a.insert(a.begin() + i + pos, x);
            }
            auto [l, r] = split(root, pos);
            auto lm = merge(l, insert_tree);
            root = merge(lm, r);
        } else if(op == "DELETE") {
            int pos, tot; cin >> pos >> tot;
            pos--;
            auto [l, mr] = split(root, pos);
            auto [m, r] = split(mr, tot);
            del(m);
            root = merge(l, r);
            // a.erase(a.begin() + pos, a.begin() + pos + tot);
        } else if(op == "MAKE-SAME") {
            int pos, tot, c; cin >> pos >> tot >> c;
            pos--;
            auto [l, mr] = split(root, pos);
            auto [m, r] = split(mr, tot);
            if(m) {
                m->assign = c;
                // assert(m->size == tot);
            }
            // cout << "l partition" << endl;
            // printTree(l);
            // cout << "m partition" << endl;
            // printTree(m);
            // cout << "r partition" << endl;
            // printTree(r);
            // auto lm = ;
            // cout << "lm partition" << endl;
            // printTree(lm);
            root = merge(merge(l, m), r);
            // for(int i = 0; i < tot; i++) a[i + pos] = c;
        } else if(op == "REVERSE") {
            int pos, tot; cin >> pos >> tot;
            pos--;
            auto [l, mr] = split(root, pos);
            auto [m, r] = split(mr, tot);
            if(m) {
                m->rev ^= 1;
            }
            // auto lm = ;
            root = merge(merge(l, m), r);
            // reverse(a.begin() + pos, a.begin() + pos + tot);
        } else if(op == "GET-SUM") {
            int pos, tot; cin >> pos >> tot;
            pos--;
            auto [l, mr] = split(root, pos);
            // cout << "l size : " << l->size << endl;
            // cout << "mr size : " << mr->size << endl;
            auto [m, r] = split(mr, tot);
            // assert(l);
            // assert(mr);
            // assert(m);
            // assert(r);
            // cout << "partition sums l : " << l->sum << ", " << " m : " << m->sum << " r : " << r->sum << '\n';
            // cout << "sum query\n";
            // cout << "treap answer\n";
            int treap_res = (m ? m->sum : 0);
            cout << treap_res << '\n';
            auto lm = merge(l, m);
            root = merge(lm, r);

            // int res = 0;
            // for(int i = 0; i < tot; i++) res += a[i + pos];
            // cout << "vector (correct answer) : " << res << '\n';

            // if(res != treap_res) {
            //     cout << "printing tree!\n";
            //     printTree(root);
            // }

            // assert(res == treap_res);

        } else if(op == "MAX-SUM") {
            // assert(root);
            // cout << "max query\n";
            // cout << "treap answer\n";
            cout << root->smax << '\n';
            // int res = 0;
            // for(int i = 0; i < a.size(); i++) {
            //     int cur = 0;
            //     for(int j = i; j < a.size(); j++) {
            //         cur += a[j];
            //         res = max(res, cur);
            //     }
            // }
            // cout << "vector (correct answer) : " << res << '\n';

            // if(res != root->smax) {
            //     cout << "printing tree!\n";
            //     printTree(root);
            // }

            // assert(res == root->smax);
        } else {
            cout << "unknown cmd : " << op << '\n';
            assert(0);
        }

        // cout << "tree status after op i : " << qq << endl;
        // printTree(root);

        // cout << "inorder" << endl;
        // inOrder(root);

        // cout << "i : " << qq << " a : " << a << '\n';

    }

    return 0;
}