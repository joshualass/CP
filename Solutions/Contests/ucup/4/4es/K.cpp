#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
very scuffed solve ... :(
very helpful to follow the kmp algorithm and learn some properties
*/

const int MOD = 998244353;

/*
3
3 3
0 1 2
7 3 
0 0 0 1 2 3 0
7 3
0 0 0 1 2 3 1
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int solve(int n, int m, vector<int> a) {
// cout << "a : " << a << endl;

    for(int i = 0; i < n; i++) {
        assert(0 <= a[i] && a[i] <= i);
    }

    int res = m;
    vector<int> root(n);
    vector<vector<int>> bad(n);

    int cnt = 0, op = 0;

    for(int i = 1; i < n && res; i++) {
        int g = a[i-1];
        // cout << "start i : " << i << " g : " << g << endl;
        vector<int> vis;
        while(a[i] != g + 1) {
            // cout << "g : " << g << endl;
            op++;
            // cout << "i : " << i << " g : " << g << endl;
            if(bad[root[g]].empty() || bad[root[g]].back() != i) {
                bad[root[g]].push_back(i);
                vis.push_back(root[g]);
            }
            
            if(g == 0) {
                g = -1; //not found
                break;
            } else {
                g = a[g - 1];
            }
            assert(op <= n);
        }

        // cout << "done g " << g << endl;
        // cout << "vis : " << vis << endl;

        if(a[i] == 0) {
            res = 1LL * res * (m - sz(vis)) % MOD;
            root[i] = i;
        } else {
            if(g == -1 || count(vis.begin(), vis.end(), root[g])) {
                res = 0;
                break;
            }
            root[i] = root[g];
        }
    }

    // cerr << "ops : " << op << endl;

    cout << res << '\n';

    return res;
}

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    solve(n, m, a);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    // for(int n = 1; n <= 8; n++) {
    //     vector<int> a(n);
    //     auto dfs = [&](auto self, int pt, vector<int> &a) -> void {
    //         if(pt == n) {
    //             solve(n, n * 2, a);
    //             return;
    //         }
    //         for(int i = 0; i <= pt; i++) {
    //             a[pt] = i;
    //             self(self, pt + 1, a);
    //         }
    //     };
    //     dfs(dfs, 0, a);
    // }

    return 0;
}