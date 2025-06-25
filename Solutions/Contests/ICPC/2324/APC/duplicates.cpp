#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
1
2
1 2
1 2

for n >= 3, when we choose a row and column, if both bad, then good, but if one bad, then the other direction should 

nvm, guaranteed n >= 3. 

*/

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<array<int,3>> ops;

    vector<int> badr, badc;
    for(int i = 0; i < n; i++) {
        set<int> s;
        for(int j = 0; j < n; j++) s.insert(a[i][j]);
        if(s.size() == n) badr.push_back(i);
    }

    for(int j = 0; j < n; j++) {
        set<int> s;
        for(int i = 0; i < n; i++) s.insert(a[i][j]);
        if(s.size() == n) badc.push_back(j);
    }


    while(badr.size() || badc.size()) {
        int r = 0, c = 0;
        int row_prim = badr.size() > badc.size();

        if(badr.size()) {
            r = badr.back();
            badr.pop_back();
        }
        if(badc.size()) {
            c = badc.back();
            badc.pop_back();
        }
        int f = -1;

        if(row_prim) {
            set<int> rs;
            for(int j = 0; j < n; j++) {
                if(j != c) {
                    rs.insert(a[r][j]);
                    f = a[r][j];    
                }
            }
            for(int i = 0; i < n; i++) {
                if(i != r && rs.count(a[i][c])) f = a[i][c];
            }
        } else {
            set<int> cs;
            for(int i = 0; i < n; i++) {
                if(i != r) {
                    cs.insert(a[i][c]);
                    f = a[i][c];
                }
            }
            for(int j = 0; j < n; j++) {
                if(j != c && cs.count(a[r][j])) f = a[r][j];
            }
        }

        //we should update it jic. 
        a[r][c] = f;
        ops.push_back({r + 1, c + 1, f});
    }
 f
    cout << ops.size() << '\n';
    for(auto op : ops) {
        for(int i = 0; i < 3; i++) cout << op[i] << " \n"[i == 2];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}