#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// SOLUTION_BEGIN
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
const ll MOD = 1e9 + 7;

const int inf = 1e9;
const int depth = 30;
struct Trie {
    struct TrieNode {
        int minidx;
        array<int,2> c;
        TrieNode() {
            minidx = inf;
            c = {-1,-1};
        }
    };
    vector<TrieNode> a;
    Trie() {
        a.push_back(TrieNode());
    }
    void insert(int x, int idx) {
        int cur = 0;
        for(int i = depth; i >= 0; i--) {
            int nx = (x >> i) & 1;
            if(a[cur].c[nx] == -1) {
                a[cur].c[nx] = a.size();
                a.push_back(TrieNode());
            }
            cur = a[cur].c[nx];
            a[cur].minidx = idx;
        }
    }
    int query(int x, int r) {
        int cur = 0, res = 0;
        for(int i = depth; i >= 0; i--) {
            int p = ((x >> i) & 1) ^ 1;
            if(a[cur].c[p] != -1 && a[a[cur].c[p]].minidx < r) {
                cur = a[cur].c[p];
                res += 1 << i;
            } else {
                assert(a[cur].c[p^1] != -1);
                cur = a[cur].c[p^1];
            }
        }
        return res;
    }
};

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a ^ b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

class MojiDeletes {
public:
    long long maximumXor(int N, int Q, int Base, int Add, int QBase, int QAdd) {
        vector<ll> a(N);
        a[0] = Add;
        Tree<int> tree(N);
        tree.update(0,Add);
        for(int i = 1; i < N; i++) {
            a[i] = (a[i-1] * Base + Add) % MOD;
            tree.update(i,a[i]);
        }
        vector<ll> l(N), r(N);
        l[0] = QAdd % N;
        r[0] = (l[0] * QBase + QAdd) % N;
        for(int i = 1; i < Q; i++) {
            l[i] = (r[i-1] * QBase + QAdd) % N;
            r[i] = (l[i] * QBase + QAdd) % N;
        }
        vector<vector<int>> queries(N);
        for(int i = 0; i < Q; i++) {
            int lo = min(l[i],r[i]), hi = max(l[i],r[i]);
            queries[lo].push_back(hi);
        }
        Trie trie;
        ll res = 0;
        for(int i = N - 1; i >= 0; i--) {
            trie.insert(a[i], i);
            for(int r : queries[i]) {
                r++;
                int x = tree.query(i,r);
                res += trie.query(x,r);
            }
        }
        return res;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg1;
  cin >> arg1;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg2;
  cin >> arg2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg3;
  cin >> arg3;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg4;
  cin >> arg4;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int arg5;
  cin >> arg5;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto c = MojiDeletes();
  long long ret = c.maximumXor(arg0, arg1, arg2, arg3, arg4, arg5);
  cout << ret;
}