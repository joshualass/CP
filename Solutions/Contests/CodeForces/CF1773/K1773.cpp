#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve(int n, int k) {
    int ok = 1;
    vector<array<int,2>> res;
    vector<int> deg(n);
    
    if(k == 1) {
        if(n == 2) {
            res.push_back({0, 1});
        } else {
            if(n >= 3) {
                for(int i = 0; i < n; i++) {
                    res.push_back({i, (i + 1) % n});
                }
            }
        }
    } else if(k == n) {
        ok = 0;
    } else {
        if(k == 2) {
            for(int i = 0; i + 1 < n; i++) {
                res.push_back({i, i + 1});
            }
        } else {
            int last = k;
            for(int i = 0; i < (k + 1) / 2; i++) {
                for(int j = i + 1; j <= last - i; j++) {
                    res.push_back({i, j});
                }
            }
            for(int i = last; i + 1 < n; i++) {
                res.push_back({i, i + 1});
            }
        }
    }
    
    if(ok) {
        cout << "YES\n";
        cout << sz(res) << '\n';
        for(auto [u, v] : res) {
            cout << u + 1 << " " << v + 1 << '\n';
            cout.flush();
            deg[u]++;
            deg[v]++;
            assert(u - v);
        }
        set<int> s(deg.begin(), deg.end());
        cout.flush();
        assert(sz(s) == k);
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int n = 1; n <= 10; n++) {
    //     for(int k = 1; k <= n; k++) {
    //         cout << "n : " << n << " k : " << k << endl;
    //         solve(n, k);
    //     }
    // }

    int n, k; cin >> n >> k;
    solve(n, k);
    

    return 0;
}
