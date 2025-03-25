#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<string> a(n);
    vector<set<int>> r(n), c(m);
    vector<int> g;
    vector<vector<int>> gid(n,vector<int>(m,-1));

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        for(int j = 0; j < m; j++) {
            if(a[i][j] != '.') {
                r[i].insert(j);
                c[j].insert(i);
            }
            if(a[i][j] == 'V' || a[i][j] == 'H') {
                gid[i][j] = g.size();
                g.push_back(-1);
            }
        }
    }

    int res = 0;

    /*
    0 - going right
    1 - going left
    2 - going down
    3 - going up
    */

    int htklarhslkdfasd;
    auto get_next_dir = [&](int i, int j, int dir) -> array<int,2> {
        if(dir == 0) { // going right
            if(r[i].upper_bound(j) == r[i].end()) {
                return {-1,-1};
            }
            int nextj = *r[i].upper_bound(j);
            return {i, nextj};
        }
        if(dir == 1) {
            if(r[i].lower_bound(j) == r[i].begin()) {
                return {-1,-1};
            }
            int nextj = *--r[i].lower_bound(j);
            return {i, nextj};
        }
        if(dir == 2) {
            if(c[j].upper_bound(i) == c[j].end()) {
                return {-1,-1};
            }
            int nexti = *c[j].upper_bound(i);
            return {nexti, j};
        }
        if(dir == 3) {
            if(c[j].lower_bound(i) == c[j].begin()) {
                return {-1,-1};
            }
            int nexti = *--c[j].lower_bound(i);
            return {nexti, j};
        }
        assert(0);
    };

    auto dfs = [&](auto self, int i, int j, int dir, int &ok, int &cost, int face_dir, vector<int> &fixed) -> void {
        // cout << "i : " << i << " j : " << j << " dir : " << dir << " ok : " << ok << " cost : " << cost << " face_dir : " << face_dir << '\n';
        if(a[i][j] == '/' || a[i][j] == '\\') {
            //redirecting signal only
            array<int,2> next;
            int nextdir = -1;
            if(a[i][j] == '/') {
                nextdir = dir ^ 3;
            }
            if(a[i][j] == '\\') {
                nextdir = dir ^ 2;
            }
            next = get_next_dir(i, j, nextdir);
            if(next != array<int,2>{-1,-1}) {
                self(self, next[0], next[1], nextdir, ok, cost, face_dir, fixed);
            }
        } else if(a[i][j] == '#') {
            //only check to make sure that nothing faces here
            if(face_dir) ok = 0;
        } else if(a[i][j] == 'V' || a[i][j] == 'H') {
            int id = gid[i][j];
            int orientation = (dir <= 1) ^ (face_dir == 1);
            // cout << "i : " << i << " j : " << j << " orientation : " << orientation << '\n';
            if(g[id] == -1) {
                g[id] = orientation;
                if(orientation != (a[i][j] == 'V')) cost++;
                fixed.push_back(id);
                for(int k = 0; k < 4; k++) {
                    array<int,2> next = get_next_dir(i, j, k);
                    // cout << "i : " << i << " j : " << j << " k : " << k << " Next : " << next << '\n';
                    if(next != array<int,2>{-1,-1}) {
                        self(self, next[0], next[1], k, ok, cost, orientation ^ (k <= 1), fixed);
                    }
                }
            } else {
                if(g[id] != orientation) {
                    ok = 0;
                    // cout << "wah wah wah not ok\n";
                }
            }
        }
    };

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(gid[i][j] != -1) {
                int id = gid[i][j];
                if(g[id] == -1) {
                    int ok_h = 1, cost_h = 0;
                    vector<int> fixed;
                    dfs(dfs, i, j, 0, ok_h, cost_h, 1, fixed);
                    for(int x : fixed) {
                        g[x] = -1;
                    }
                    fixed.clear();
                    int ok_v = 1, cost_v = 0;
                    dfs(dfs, i, j, 2, ok_v, cost_v, 1, fixed);
                    for(int x : fixed) {
                        g[x] = -1;
                    }
                    fixed.clear();
                    // cout << "i : " << i << " j : " << j << " ok_h : " << ok_h << " cost_h : " << cost_h << " ok_v : " << ok_v << " cost_v : " << cost_v << '\n';
                    if(ok_h == 0 && ok_v == 0) {
                        cout << "-1\n";
                        return 0;
                    }
                    int best_dir = -1;
                    if(ok_h == 0) {
                        best_dir = 2;
                    } else if(ok_v == 0) {
                        best_dir = 0;
                    } else if(cost_h < cost_v) {
                        best_dir = 0;
                    } else {
                        best_dir = 2;
                    }

                    dfs(dfs, i, j, best_dir, ok_h, res, 1, fixed);
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}
