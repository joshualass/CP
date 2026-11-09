#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<int, map<int,int>> mx, my;
    vector<array<int,2>> a;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        mx[x][y] = i;
        my[y][x] = i;
        a.push_back({x, y});
    }

    vector<int> order;
    vector<int> cy, cx;
    for(auto [k, v] : mx) {
        if(sz(v) == 1) cx.push_back(k);
    }
    for(auto [k, v] : my) {
        if(sz(v) == 1) cy.push_back(k);
    }

    int cycle = 0;

    while(1) {
        // cout << cycle++ << endl;
        set<int> s;
        for(auto x : cx) {
            if(sz(mx[x]) == 1) {
                s.insert(mx[x].begin()->second);
            }
        }
        for(auto y : cy) {
            if(sz(my[y]) == 1) {
                s.insert(my[y].begin()->second);
            }
        }
        cx.clear();
        cy.clear();
        if(s.empty()) break;
        vector<int> b(s.begin(), s.end());
        reverse(b.begin(), b.end());
        for(int id : b) {
            auto [x, y] = a[id];
            // cout << "remove point id : " << id << " x : " << x << " y : " << y << endl;
            mx[x].erase(y);
            if(sz(mx[x]) == 1) cx.push_back(x);
            my[y].erase(x);
            if(sz(my[y]) == 1) cy.push_back(y);
            order.push_back(id);
        }
    }

    int res;
    if(sz(order) == n) {
        res = order.back();
    } else {
        res = n;
        for(auto [x, info] : mx) {
            for(auto [y, id] : info) {
                res = min(res, id);
            }
        }
        assert(res != n);
    }

    cout << res + 1 << '\n';

    return 0;
}
