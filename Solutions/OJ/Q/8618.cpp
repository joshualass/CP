#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

unordered_map<int,int> trie[100001];
vector<int> attrie[100001];
int trie_idx = 0;

void add(vector<int> a, int q) {
    int cur = 0;
    for(int x : a) {
        if(trie[cur].count(x) == 0) {
            trie[cur][x] = ++trie_idx;
        }
        cur = trie[cur][x];
    }
    attrie[cur].push_back(q);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;
    vector<array<int,2>> a(m);
    for(auto &x : a) for(auto &y : x) {
        cin >> y;
        y--;
    }

    vector<int> cnts(q, 1e9), res(q, INT_MAX);
    map<array<int,2>, set<int>> adjs;
    map<vector<int>, vector<int>> short_queries;

    for(int i = 0; i < q; i++) {
        int k; cin >> k;
        // if(false) {
        if(k <= 20) {
            vector<int> b(k);
            for(int &x : b) cin >> x;
            add(b, i);
        } else {
            int p; cin >> p;
            cnts[i] = k - 1;
            for(int j = 1; j < k; j++) {
                int x; cin >> x;
                adjs[{p,x}].insert(i);
                if(x == p + 1) cnts[i]--;
                p = x;
            }
        }
    }

    for(int i = 0; i < q; i++) {
        if(cnts[i] == 0) res[i] = 0;
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);

    auto upd = [&](array<int,2> rem, int val, int time) -> void {
        if(adjs.count(rem)) {
            vector<int> torem;
            for(int x : adjs[rem]) {
                cnts[x] += val;
                if(cnts[x] == 0) {
                    res[x] = min(res[x], time + 1);
                    torem.push_back(x);
                }
            }
            for(int x : torem) adjs[rem].erase(x);
        }
    };

    auto upd1 = [&](int x, int val, int time) -> void {
        if(x) {
            array<int,2> rem = {perm[x-1], perm[x]};
            upd(rem, val, time);
        }
        if(x + 1 < n) {
            array<int,2> rem = {perm[x], perm[x+1]};
            upd(rem, val, time);
        }
    };

    auto updshort = [&](int x, int time) -> void {
        for(int i = max(0, x - 19); i <= x; i++) {
            int cur = 0;
            for(int j = i; j - i < 20 && j < n; j++) {
                if(trie[cur].count(perm[j]) == 0) break;
                cur = trie[cur][perm[j]];
                for(int x : attrie[cur]) {
                    res[x] = time + 1;
                }
                attrie[cur].clear();
            }
        }
    };


    for(int i = 0; i < n; i++) {
    //     upd({i, i + 1}, 0, -1);
        updshort(i, -1);
    }

    // cout << "starting counts : " << cnts << '\n';

    for(int i = 0; i < m; i++) {
        auto [x, y] = a[i];
        upd1(x, 1, i);
        upd1(y, 1, i);
        if(x + 1 == y) {
            upd(array<int,2>{perm[x],perm[y]}, -1, i);
        }
        swap(perm[x], perm[y]);
        if(x + 1 == y) {
            upd(array<int,2>{perm[x],perm[y]}, 1, i);
        }
        upd1(x, -1, i);
        upd1(y, -1, i);
        // cout << "i : " << i << " cnts : " << cnts << '\n';

        updshort(x, i);
        updshort(y, i);

    }

    for(int x : res) cout << x << '\n';

    return 0;
}