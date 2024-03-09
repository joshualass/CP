#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = INT_MIN;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
    }
    // optional MIQ stuff
    bool cond(T a, T b) {
        return a <= b;
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
            if(curr & 1) { //non
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
    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
        pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
        return ans;
    }   
    pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(cond(val, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (currl + currr) / 2;
            if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
            return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        } else {
            return {-1,base};
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(1) {
        int n; cin >> n;
        Tree<int> tree(n);
        vector<int> years(n);
        for(int i = 0; i < n; i++) {
            int y, r; cin >> y >> r;
            years[i] = y;
            tree.update(i,r);
        }
        // cout << "years : " << years << '\n';
        int M; cin >> M;
        for(int i = 0; i < M; i++) {
            int y, x; cin >> y >> x;
            int ly = 0, ry = n - 1;
            while(ly != ry) {
                int m = ly + (ry - ly) / 2;
                if(years[m] >= y) {
                    ry = m;
                } else {
                    ly = m + 1;
                }
            }
            int lx = 0, rx = n - 1;
            while(lx != rx) {
                int m = lx + (rx - lx + 1) / 2;
                if(years[m] <= x) {
                    lx = m;
                } else {
                    rx = m - 1;
                }
            }
            //check if everything is known
            // cout << "ly : " << ly << " lx : " << lx << '\n';
            if(x - y == rx - ry) {
                // cout << "allknown ---\n";
                if(tree.at(lx) <= tree.at(ly) && tree.query(ly+1,lx) < tree.at(lx)) {
                    cout << "true\n";
                } else {
                    cout << "false\n";
                }
            } else {//something is not known
                
                if(y == years[ly] && x == years[lx]) { //both known
                    if(tree.at(lx) <= tree.at(ly) && tree.query(ly+1,lx) < tree.at(lx)) {
                        cout << "maybe\n";
                    } else {
                        cout << "false\n";
                    }
                } else if(y == years[ly]) { //y known
                    if(tree.query(ly+1,lx+1) < tree.at(ly)) {
                        cout << "maybe\n";
                    } else {
                        cout << "false\n";
                    }
                } else if(x == years[lx]) {//x known
                    if(tree.query(ly,lx) < tree.at(lx)) {
                        cout << "maybe\n";
                    } else {
                        cout << "false\n";
                    }
                } else {//neither known
                    cout << "maybe\n";
                }
            }
        }
        if(n == 0) break;
        cout << '\n';
    }

    return 0;
}