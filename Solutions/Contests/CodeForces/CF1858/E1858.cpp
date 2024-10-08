#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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
    bool isLeaf(int idx) {
        return idx >= size;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Tree<int> tree(1e6);
    vector<set<int>> s(1e6);
    vector<vector<int>> history(1e6);
    vector<array<int,2>> qhist;

    int q; cin >> q;
    int curr_size = 0;

    auto addElement = [&](int idx, int val) -> void {
        // cout << "inserting idx : " << idx << " val : " << val << '\n';
        set<int>::iterator it = s[val].lower_bound(0);
        if(it != s[val].end()) {
            tree.update((*it),0);
        }
        s[val].insert(idx);
        tree.update(*s[val].lower_bound(0),1);
        history[idx].push_back(val);
    };

    auto eraseElement = [&](int idx) -> void {
        int val = history[idx].back();
        // cout << "erasing idx : " << idx << " val : " << val << '\n';
        s[val].erase(idx);
        tree.update(idx,0);
        set<int>::iterator it = s[val].lower_bound(0);
        if(it != s[val].end()) {
            tree.update((*it),1);
        }
        history[idx].pop_back();
    };

    for(int i = 0; i < q; i++) {
        char type; cin >> type;
        if(type == '+') {
            int x; cin >> x;
            x--;
            if(history[curr_size].size()) {
                int prevv = history[curr_size].back();
                eraseElement(curr_size);
                history[curr_size].push_back(prevv);
            }
            addElement(curr_size, x);
            curr_size++;
            qhist.push_back({0,x});
        } else if(type == '-') {
            int k; cin >> k;
            curr_size -= k;
            qhist.push_back({1,k});
        } else if(type == '!') {
            if(qhist.back()[0] == 0) { //last thing we did we add
                curr_size--;
                eraseElement(curr_size);
                if(history[curr_size].size()) { //add previous element back here
                    int last = history[curr_size].back();
                    history[curr_size].pop_back();
                    addElement(curr_size,last);
                }
            } else { //last thing we did was remove k elements
                curr_size += qhist.back()[1];
            }
            qhist.pop_back();
        } else {
            cout << tree.query(0,curr_size) << endl;
        }
        // cout << "i : " << i << " curr size : " << curr_size << '\n';
        // cout << "tree\n" << tree.v << '\n';
    }

    return 0;
}