#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
nice casework problem; need to work on time complexity

marko slices through this casework
*/

void solve() {
    
    int n; cin >> n;
    map<int,set<int>> m;
    for(int i = 0; i < n; i++) {
        int c, d; cin >> c >> d;
        m[c].insert(d);
    }

    auto get_next = [&](int row, int ge) -> int {
        while(m[row].count(ge)) ge++;
        return ge;
    };

    int done = 0, bad = 0;
    int l = 0, r = 1;
    vector<int> prev;
    for(int row = 0; ; row++) {
        auto it = m[row].lower_bound(l);
        while(it != m[row].end() && (*it) < r) {
            prev.push_back(*it);
            it++;
        }
        if(sz(prev) >= 3) {
            bad = 1;
            break;
        }
        if(prev.empty()) {
            done = 1;
            break;
        } else if(sz(prev) == 1) {
            int nr = get_next(row, r);
            l = prev[0];
            r = nr;
            prev.clear();
        } else if(sz(prev) == 2) {
            sort(prev.begin(), prev.end());
            int nr = get_next(row, prev[1] + 1);
            if(nr != r) {
                bad = 1;
                break;
            }
            int nnr = get_next(row, nr + 1);
            l = prev[0];
            r = nnr;
            prev = {prev[1]};
        } else {
            assert(0);
        }
    }

    assert((done ^ bad));
    if(done) {
        cout << "YES\n";
    }
    if(bad) {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}