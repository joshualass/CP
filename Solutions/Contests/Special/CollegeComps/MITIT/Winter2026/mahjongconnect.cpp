#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
thinking a lot about max flow and bfs, play around with many examples
intuition helps me guess that we can always somehow do it with even sized component
to construct dfs tree, we can merge children and return unmatched child to parent!
*/

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<array<int,3>> a(n);
    vector<int> cx, cy;
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
        cx.push_back(x[0]);
        cy.push_back(x[1]);
    }

    eraseduplicates(cx);
    eraseduplicates(cy);

    int xs = sz(cx), ys = sz(cy);
    vector<map<int,int>> r(xs), c(ys);

    for(int i = 0; i < n; i++) {
        a[i][0] = lower_bound(cx.begin(), cx.end(), a[i][0]) - cx.begin();
        a[i][1] = lower_bound(cy.begin(), cy.end(), a[i][1]) - cy.begin();
        auto [x, y, t] = a[i];
        r[x][y] = i;
        c[y][x] = i;
    }

    int ok = 1;
    vector<array<int,2>> res;
    vector<int> vis(n);

    auto fndir = [&](int i, int dir) -> int {
        if(dir == 0) { 
            int x = a[i][0];
            auto it = r[x].upper_bound(a[i][1]);
            if(it == r[x].end()) return -1;
            return it->second;
        } else if(dir == 1) {
            int y = a[i][1];
            auto it = c[y].upper_bound(a[i][0]);
            if(it == c[y].end()) return -1;
            return it->second;
        } else if(dir == 2) {
            int x = a[i][0];
            auto it = r[x].lower_bound(a[i][1]);
            if(it == r[x].begin()) return -1;
            return (--it)->second;
        } else if(dir == 3) {
            int y = a[i][1];
            auto it = c[y].lower_bound(a[i][0]);
            if(it == c[y].begin()) return -1;
            return (--it)->second;
        } else {
            assert(0);
        }
    };

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < 4; j++) {
    //         cout << "i : " << i << " j : " << j << endl;
    //         fndir(i, j);
    //     }
    // }

    auto dfs = [&](auto self, int i, int par_dir) -> int {
        // cout << "i : " << i << " pd : " << par_dir << endl;
        vis[i] = 1;
        vector<int> c(4, -1);
        for(int j = 0; j < 4; j++) {
            int ch = fndir(i, j);
            if(ch != -1 && vis[ch] == 0 && a[ch][2] == a[i][2]) {
                ch = self(self, ch, j);
                c[j] = ch;
            }
        }

        // cout << "c : " << c << endl;

        for(int j = 0; j < 2; j++) {
            if(c[j] != -1 && c[j + 2] != -1) {
                res.push_back({c[j], c[j+2]});
                c[j] = -1;
                c[j+2] = -1;
            }
        }

        int use = 0;
        for(int j = 0; j < 4; j++) {
            if(use == 0 && j != par_dir && c[j] != -1) {
                use = 1;
                res.push_back({i, c[j]});
                c[j] = -1;
            }
        }

        if(par_dir != -1 && use == 0 && c[par_dir] != -1) {
            use = 1;
            res.push_back({i, c[par_dir]});
            c[par_dir] = -1;
        }

        if(use == 0) return i;
        for(int j = 0; j < 4; j++) {
            if(c[j] != -1) {
                assert(par_dir == -1 || j == par_dir);
                return c[j];
            }
        }
        return -1;
    };

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            int last = dfs(dfs, i, -1);
            // cout << "last : " << last << endl;
            if(last != -1) ok = 0;
        }
    }

    if(ok) {
        cout << "YES\n";
        for(auto [i, j] : res) cout << i + 1 << " " << j + 1 << '\n';
    } else {
        cout << "NO\n";
    }

    return 0;
}
