#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
try making O(n sqrt n) runtime with O(n) memory
none of the homies like using n logn memory XXXX

memory forces

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int SQN = 550;

struct Info {
    int res, l, r, all;
    Info(): res(0), l(0), r(0), all(0) {}
    Info(int res, int l, int r, int all): res(res), l(l), r(r), all(all) {}
};

Info operator+(Info &lhs, Info &rhs) {
    Info res;
    res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
    res.l = max(lhs.l, lhs.all + rhs.l);
    res.r = max(rhs.r, rhs.all + lhs.r);
    res.all = lhs.all + rhs.all;
    return res;
}

void solve() {
    
    int n, q; cin >> n >> q;

    vector<vector<array<int,2>>> bidx(n); //[value], stores {present block id, idx in bvals}
    vector<vector<int>> bvals;
    vector<Info> infos;

    set<array<int,2>> vals;

    auto get_val = [&](int val) -> array<int,2> {
        int p = 0;
        Info res;
        for(int i = 0; i < (n + SQN - 1) / SQN; i++) {
            Info nx;
            if(p < bidx[val].size() && i == bidx[val][p][0]) {
                nx = infos[bidx[val][p++][1]];
            } else {
                nx = Info(0, 0, 0, -SQN);
            }
            res = res + nx;
        }
        array<int,2> rv = {res.res, val};
        // cout << "rv : " << rv << '\n';
        return rv;
    };

    auto update_info = [&](int bvidx, int block_id) -> void {
        int res = 0, l = 0, r = 0;
        for(int i = block_id * SQN, p = 0, cur = 0, curl; i < (block_id + 1) * SQN; i++) {
            int in = 0;
            if(p < bvals[bvidx].size() && i == bvals[bvidx][p]) {
                in = 1;
                p++;
            }
            if(in) {
                cur++;
                curl++;
            } else {
                cur--;
                curl--;
            }
            cur = max(cur, 0);

            res = max(res, cur);
            l = max(res, curl);
        }

        for(int i = (block_id + 1) * SQN - 1, p = bvals[bvidx].size() - 1, cur = 0; i >= block_id * SQN; i--) {
            int in = 0;
            if(p >= 0 && i == bvals[bvidx][p]) {
                in = 1;
                p--;
            }
            if(in) {
                cur++;
            } else {
                cur--;
            }
            r = max(r, cur);
        }

        int all = -SQN * bvals[bvidx].size() * 2;
        infos[bvidx] = Info(res, l, r, all);
    };

    auto insert = [&](int idx, int val) -> void {
        // cout << "insert called idx : " << idx << " val : " << val << '\n';
        vals.erase(get_val(val));

        int block_id = idx / SQN;

        int i = 0;
        while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
        if(!(i < bidx[val].size() && bidx[val][i][0] == block_id)) {
            bidx[val].insert(bidx[val].begin() + i, {block_id, (int) bvals.size()});
            bvals.push_back({});
            infos.push_back(Info());
        }

        int bvidx = bidx[val][i][1];
        
        i = 0;
        while(i < bvals[bvidx].size() && idx > bvals[bvidx][i]) i++;
        bvals[bvidx].insert(bvals[bvidx].begin() + i, idx);

        update_info(bvidx, block_id);

        vals.insert(get_val(val));
    };

    auto erase = [&](int idx, int val) -> void {
        vals.erase(get_val(val));

        int block_id = idx / SQN;

        int i = 0;
        while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
        int bvidx = bidx[val][i][1];
        int p = 0;

        if(bvidx >= bvals.size() || count(bvals[bvidx].begin(), bvals[bvidx].end(), idx) == 0) {
            cout << "idx : " << idx << " val : " << val << '\n';

            cout << "i : " << i << '\n';
            cout << "bvidx : " << bvidx << '\n';
            for(int i = 0; i < n; i++) {
                cout << "i : " << i << " bidx[i] : " << bidx[i] << '\n';
            }
            for(int i = 0; i < bvals.size(); i++) {
                cout << "i : " << i << " bvals[i] : " << bvals[i] << '\n';
            }

            assert(0);
        }

        while(bvals[bvidx][p] != idx) p++;
        bvals[bvidx].erase(bvals[bvidx].begin() + p);

        update_info(bvidx, block_id);

        vals.insert(get_val(val));
    };

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        insert(i, a[i]);
    }

    vals.insert({0, -1});

    for(int tr = 0; tr < q; tr++) {
        int i, x; cin >> i >> x;
        i--, x--;
        erase(i, a[i]);
        a[i] = x;
        insert(i, x);
        cout << (*--vals.end())[0] / 2 << " \n"[tr == q - 1];
        // cout << (*--vals.end())[0] << " \n"[tr == q - 1];
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}