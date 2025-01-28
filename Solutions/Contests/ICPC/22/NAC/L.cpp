#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Tree {
    vector<set<array<int,3>>> v;
    int n, size;
    Tree(int n = 0) {
        this->n = n;
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void update(int pos, array<int,3> val) {
        assert(pos < n && pos >= 0);
        int cur = pos + size;
        while(cur != 1) {
            //do stuff
            // cout << "cur : " << cur << " add to cur : " << val[0] << ", " << val[1] << ", " << val[2] << '\n';
            v[cur].insert(val);        
            cur /= 2;
        }
        v[cur].insert(val);        
    }
    vector<int> query(int l, int r, int loy, int hiy) {
        vector<int> res;
        // cout << "l : " << l << " r : " << r << " loy : " << loy << " hiy : " << hiy << endl;
        _query(1,0,size,l,r, res, loy, hiy);
        return res;
    }
    void _query(int idx, int currl, int currr, int &targetl, int &targetr, vector<int> &res, int loy, int hiy) {
        if(currr <= targetl || currl >= targetr || res.size() > 75) return;
        if(currl >= targetl && currr <= targetr) {
            set<array<int,3>>::iterator it = v[idx].lower_bound({loy,-1});
            // cout << "gogog idx : " << idx << " size : " << v[idx].size() << '\n';
            while(it != v[idx].end() && (*it)[0] <= hiy && res.size() <= 75) {
                res.push_back((*it)[1]);
                it++;
            }
            return;
        }
        int mid = (currl + currr) / 2;
        _query(idx * 2, currl, mid, targetl, targetr, res, loy, hiy);
        _query(idx * 2 + 1, mid, currr, targetl, targetr, res, loy, hiy);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    set<int> xs, ys;
    vector<array<int,3>> a(n);
    for(int i = 0; i < n; i++) {
        int x, y, h; cin >> x >> y >> h;
        a[i] = {x,y,h};
        xs.insert(x);
        ys.insert(y);
    }

    vector<array<int,4>> qu(q);
    for(int i = 0; i < q; i++) {
        int xl, yl, xh, yh; cin >> xl >> yl >> xh >> yh;
        xs.insert(xl);
        xs.insert(xh);
        ys.insert(yl);
        ys.insert(yh);
        qu[i] = {xl,yl,xh,yh};
    }

    map<int,int> mcx, mcy;
    int i = 0;
    for(int x : xs) {
        mcx[x] = i++;
    }
    i = 0;
    for(int y : ys) {
        mcy[y] = i++;
    }
    // for(auto [x, to_x] : mcx) cout << "x : " << x << " to_x : " << to_x << '\n';
    for(auto &x : a) {
        x[0] = mcx[x[0]];
        x[1] = mcy[x[1]];
    }
    for(auto &x : qu) {
        x[0] = mcx[x[0]];
        x[1] = mcy[x[1]];
        x[2] = mcx[x[2]];
        x[3] = mcy[x[3]];
    }
    // for(int i = 0; i < n; i++) {
    //     cout << a[i][0] << ", " << a[i][1] << ", " << a[i][2] << '\n';
    // }
    Tree tree(mcx.size());

    for(auto [x, y, h] : a) {
        tree.update(x, {y,h,x});
    }

    auto can_make_tri = [&](vector<int> res) -> bool {
        sort(res.begin(), res.end());
        for(int i = 2; i < res.size(); i++) {
            if(res[i-2] + res[i-1] > res[i]) return 1;
        }
        return 0;
    };

    for(int i = 0; i < q; i++) {
        vector<int> res = tree.query(qu[i][0], qu[i][2] + 1, qu[i][1], qu[i][3]);
        // cout << "i : " << i << '\n';
        // for(int x : res) cout << x << ' ';
        // cout << '\n';
        cout << can_make_tri(res) << '\n';
    }


    return 0;
}