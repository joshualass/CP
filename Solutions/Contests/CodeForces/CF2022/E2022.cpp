#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

struct component {

    map<int,pair<int,set<int>>> rows, cols;
    int size;

    component() {
        size = 0;
    }

    int insertElement(int r, int c, int x) {
        if(rows.count(r) && cols.count(c)) {
            return (rows[r].first ^ cols[c].first) == x;
        } else if(rows.count(r)) {
            cols[c] = {rows[r].first ^ x,{}};
        } else if(cols.count(c)) {
            rows[r] = {cols[c].first ^ x, {}};
        } else {
            rows[r] = {0, {}};
            cols[c] = {x, {}};
        }
        rows[r].second.insert(c);
        cols[c].second.insert(r);
        size++;
        return 1;
    }

    void mergeComponent(component comp, int sr, int sc) {
        queue<array<int,2>> q;
        comp.rows[sr].second.erase(sc);
        comp.cols[sc].second.erase(sr);
        q.push({sr,sc});
        while(q.size()) {
            auto [r, c] = q.front();
            // cerr << "r : " << r << " c : " << c << endl;
            q.pop();
            insertElement(r,c, comp.rows[r].first ^ comp.cols[c].first);

            while(comp.rows[r].second.size()) {
                int nc = *comp.rows[r].second.begin();
                q.push({r,nc});
                comp.rows[r].second.erase(nc);
                comp.cols[nc].second.erase(r);
            }

            while(comp.cols[c].second.size()) {
                int nr = *comp.cols[c].second.begin();
                q.push({nr,c});
                comp.cols[c].second.erase(nr);
                comp.rows[nr].second.erase(c);
            }
        }
    }

};

void solve() {

    int n, m, k, q; cin >> n >> m >> k >> q;
    map<int,component> components;
    vector<int> rows(n,-1), cols(m,-1);
    int usedrowscols = 0;
    int id = 0, ok = 1;

    ll mult = binexp(2,30);

    auto getAns = [&]() -> ll {
        if(ok == 0) return 0;
        ll dof = n + m - 1 - usedrowscols + components.size();
        // cout << "const : " << n + m - 1 << " used rc : " << usedrowscols << " comps : " << components.size() << '\n';
        // cerr << "dof : " << dof << endl;
        return binexp(mult,dof);
    };
    
    auto addGrid = [&](int r, int c, int x) -> void {
        // cerr << "add grid\n";
        if(rows[r] == -1 && cols[c] == -1) {
            component comp;
            comp.insertElement(r,c,x);
            rows[r] = id;
            cols[c] = id;
            components[id++] = comp;
            usedrowscols += 2;
            // cerr << "l1\n";
        } else if(rows[r] == -1) {
            components[cols[c]].insertElement(r,c,x);
            rows[r] = cols[c];
            usedrowscols++;
            // cerr << "l2\n";

        } else if(cols[c] == -1) {
            components[rows[r]].insertElement(r,c,x);
            cols[c] = rows[r];
            usedrowscols++;
            // cerr << "l3\n";

        } else {

            // cerr << "l4\n";
            if(rows[r] == cols[c]) {
                int okmerge = components[rows[r]].insertElement(r,c,x);
                if(!okmerge) {
                    ok = 0;
                }

                // cerr << "l5\n";
            } else {
                components[rows[r]].insertElement(r,c,x);
                components[cols[c]].insertElement(r,c,x);
                int comp_id = -1, prev_comp_id = -1;
                if(components[rows[r]].size > components[cols[c]].size) {
                    comp_id = rows[r];
                    prev_comp_id = cols[c];
                } else {
                    comp_id = cols[c];
                    prev_comp_id = rows[r];
                }
                // cerr << "l6\n";

                
                components[comp_id].mergeComponent(components[prev_comp_id], r, c);
                for(auto [row, s] : components[prev_comp_id].rows) {
                    rows[row] = comp_id;
                }
                for(auto [col, s] : components[prev_comp_id].cols) {
                    cols[col] = comp_id;
                }
                components.erase(prev_comp_id);
            }
        }
    };

    for(int i = 0; i < k; i++) {
        int r, c, v; cin >> r >> c >> v;
        r--; c--;
        addGrid(r,c,v);
        // cerr << "survive i : " << i << endl;
    }

    cout << getAns() << '\n';
    for(int i = 0; i < q; i++) {
        int r, c, v; cin >> r >> c >> v;
        r--; c--;
        addGrid(r,c,v);
        cout << getAns() << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}