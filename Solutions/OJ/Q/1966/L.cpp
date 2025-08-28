#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
very easy pz world finals implementation problem
*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

vector<int> dx = {1, 0, -1, 0}, dy = {0, -1, 0, 1};
vector<string> a;

bool debug_mode = 0;
int jdir;
int jr, jc;
int jget_dist() {
    int ans = 0;
    int pr = jr, pc = jc;
    while(1) {
        pr += dx[jdir], pc += dy[jdir];
        if(pr < 0 || pc < 0 || pr >= a.size() || pc >= a[0].size()) break;
        if(a[pr][pc] == '#') break;
        ans ++;
    }
    return ans;
}

int interactor(string s) {
    cout << s << endl;
    int ans;
    if(debug_mode) {
        if(s == "left") {
            jdir --;
            if(jdir == -1) jdir = 3;
        }
        else if(s == "right") {
            jdir = (jdir + 1) % 4;
        }
        else if(s == "step") {
            jr += dx[jdir], jc += dy[jdir];
            assert(jr >= 0 && jc >= 0 && jr < a.size() && jc < a[0].size());
            assert(a[jr][jc] == '.');
        }
        else assert(false);
        ans = jget_dist();
        cout << "INTERACT : " << jr << " " << jc << " " << jdir << " " << ans << "\n";
    }
    else {
        cin >> ans;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c; cin >> r >> c;

    a = vector<string>(r);
    for(auto &x : a) cin >> x;

    if(debug_mode) {
        cin >> jr >> jc >> jdir;
    }

    map<array<int,2>, int> m;
    int dir = 0, dist = -1;

    auto go = [&](int op) -> void {
        if(op == 0) {
            dir = (dir + 3) % 4;
            dist = interactor("left");
        } else if(op == 1) {
            dir = (dir + 1) % 4;
            dist = interactor("right");
        } else if(op == 2) {
            dist = interactor("step");
        }
    };


    auto upd_dir = [&](int targ) -> void {
        if((dir + 3) % 4 == targ) {
            go(0);
        } else {
            while(dir != targ) go(1);
        }
    };

    auto dfs = [&](auto self, int x, int y) -> void {
        m[{x, y}] = 0;
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(m.count({nx, ny}) == 0) {
                upd_dir(i);
                if(dist == 0) {
                    m[{nx,ny}] = 1;
                } else {
                    go(2);
                    self(self, nx, ny);
                    upd_dir(i ^ 2);
                    go(2);
                }
            }
        }
    };

    int sd;
    if(debug_mode) sd = jget_dist();
    else cin >> sd;

    dist = sd;

    dfs(dfs, 0, 0);

    int mx = max(r,c);
    vector hv(5, vector(mx, vector<ll>(mx)));
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < mx; j++) {
            for(int k = 0; k < mx; k++) {
                hv[i][j][k] = rng() & ((1LL << 40) - 1);
            }
        }
    }

    auto get_hash = [&](vector<array<int,2>> &coords) -> array<ll,5> {
        array<ll,5> res = {};
        for(int i = 0; i < 5; i++) {
            for(auto [row, col] : coords) {
                res[i] += hv[i][row][col];
            }
        }
        return res;
    };

    int minr = 0, minc = 0;
    int maxr = 0, maxc = 0;
    for(auto [k, v] : m) {
        if(v == 0) {
            minr = min(minr, k[0]);
            minc = min(minc, k[1]);
            maxr = max(maxr, k[0]);
            maxc = max(maxc, k[1]);
        }
    }

    int sr = -minr, sc = -minc; 

    int tr = (maxr + minr) / 2, tc = (maxc + minc) / 2;
    if(m.count({tr, tc}) && m[{tr, tc}] == 0) {
        map<array<int,2>, int> par_dir;
        queue<array<int,2>> q;
        par_dir[{tr, tc}] = -1;
        q.push({tr,tc});
        while(q.size()) {
            auto [row, col] = q.front();
            q.pop();
            for(int i = 0; i < 4; i++) {
                int nr = row + dx[i], nc = col + dy[i];
                if(m.count({nr,nc}) && m[{nr,nc}] == 0 && par_dir.count({nr,nc}) == 0) {
                    q.push({nr,nc});
                    par_dir[{nr,nc}] = i ^ 2;
                }
            }
        }
        int cr = 0, cc = 0;
        while(cr != tr || cc != tc) {
            assert(par_dir.count({cr,cc}));
            upd_dir(par_dir[{cr, cc}]);
            cr += dx[dir];
            cc += dy[dir];
            go(2);
        }
        sr = tr - minr, sc = tc - minc;
    }

    vector par(r, vector<int>(c));

    vector<array<int,2>> coords;
    for(auto [k, v] : m) {
        if(v == 0) {
            coords.push_back({k[0] - minr, k[1] - minc});
        }
    }

    auto rotate = [&]() -> void {
        vector<array<int, 2>> res;
        for(auto [row, col] : coords) {
            res.push_back({-col, row});
        }
        int minr = 1e9, minc = 1e9;
        for(int i = 0; i < res.size(); i++) minr = min(minr, res[i][0]), minc = min(minc, res[i][1]);
        int nsr = -sc, nsc = sr;
        sr = nsr - minr;
        sc = nsc - minc;
        for(int i = 0; i < res.size(); i++){
            res[i][0] -= minr;
            res[i][1] -= minc;
        }
        coords = res;
    };

    vector<vector<int>> vis(r, vector<int>(c));
    set<array<int,2>> cands;

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            vector<array<int,2>> pts;
            queue<array<int,2>> q;
            q.push({i, j});
            while(q.size()) {
                auto [x, y] = q.front();
                q.pop();
                if(vis[x][y] || a[x][y] == '#') continue;
                vis[x][y] = 1;
                pts.push_back({x, y});
                for(int k = 0; k < 4; k++) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if(nx >= 0 && nx < r && ny >= 0 && ny < c) {
                        q.push({nx, ny});
                    }
                }
            }
            int mr = r, mc = c;
            for(auto [row, col] : pts) {
                mr = min(mr, row);
                mc = min(mc, col);
            }
            for(auto &pt : pts) {
                pt[0] -= mr;
                pt[1] -= mc;
            }
            for(int k = 0; k < 4; k++) {
                if(get_hash(coords) == get_hash(pts)) {
                    cands.insert({mr + sr, mc + sc});
                }
                rotate();
            }
        }
    }

    assert(cands.size());
    
    if(cands.size() == 1) {
        auto [row, col] = *cands.begin();
        cout << "yes " << row + 1 << " " << col + 1 << endl;
    } else {
        cout << "no" << endl;
    }

    if(debug_mode) {
        cout << "ACTUAL : " << jr + 1 << " " << jc + 1 << "\n";
    }

    return 0;
}