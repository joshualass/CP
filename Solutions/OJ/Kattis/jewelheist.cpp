#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

struct Tree {
    vector<vector<int>> v;
    int n, size;
    Tree(int n) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void update(int pos, int val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].push_back(val);
        while(curr != 1) {
            v[curr / 2].push_back(val);
            curr /= 2;
        }
    }
    void build_all() {
        for(int i = 0; i < v.size(); i++) {
            v[i].push_back(INT_MAX);
            sort(v[i].begin(), v[i].end());
        }
    }
    int query(int l, int r, int time) {//queries in range [l,r)
        return _query(1,0,size,l,r, time);
    }
    int _query(int idx, int currl, int currr, int &targetl, int &targetr, int time) {
        if(currr <= targetl || currl >= targetr) return 0;
        if(currl >= targetl && currr <= targetr) {
            return lower_bound(v[idx].begin(), v[idx].end(), time) - v[idx].begin();
        }
        int mid = (currl + currr) / 2;
        return _query(idx * 2, currl, mid, targetl, targetr, time) + _query(idx * 2 + 1, mid, currr, targetl, targetr, time);
    }
};

void solve() {
    
    int n, k; cin >> n >> k;
    vector<array<int,3>> a(n);
    set<int> xs, ys;
    vector<vector<array<int,2>>> b(k);
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
        xs.insert(x[0]);
        ys.insert(x[1]);
        x[2]--;
    }

    map<int,int> cx, cy;
    int p = 0;
    for(int x : xs) cx[x] = p++;
    p = 0;
    for(int y : ys) cy[y] = p++;

    int xp = xs.size();

    Tree tree(xp);
    for(auto &x : a) {
        x[0] = cx[x[0]];
        x[1] = cy[x[1]];
        // cout << "x : " << x[0] << " y : " << x[1] << " k : " << x[2] << endl;
        b[x[2]].push_back({x[0], x[1]});
        tree.update(x[0], x[1]);
    }

    // cout << "xp : " << xp << endl;

    int res = 0; 
    
    auto ttfang = [&](int xlo, int xhi, int lttime) -> void {
        xlo++;
        int q = tree.query(xlo, xhi, lttime);
        // cout << "xlo : " << xlo << " xhi : " << xhi << " lttime : " << lttime << " count : " << q << endl;
        res = max(res, q);
    };

    tree.build_all();

    // cout << "tree front : " << tree.v[1] << endl;

    for(int i = 0; i < k; i++) {
        // cout << "exclude color i : " << i << endl;
        map<int,int> m;
        m[-1] = 1;
        m[xp] = 1;
        map<int,vector<int>> aty;
        for(auto [x, y] : b[i]) {
            m[x]++;
            // cout << "add x : " << x << endl;
            aty[y].push_back(x);
        }
        int prev = -1;
        for(auto [x, _] : m) {
            if(x != -1) {
                ttfang(prev, x, INT_MAX);
            }
            prev = x;
        }
        for(auto rit = aty.rbegin(); rit != aty.rend(); rit++) {
            for(int x : rit->second) {
                m[x]--;
                if(m[x] == 0) {
                    m.erase(x);
                    int xhi = m.upper_bound(x)->first;
                    int xlo = (--m.upper_bound(x))->first;
                    ttfang(xlo, xhi, rit->first);
                }
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}