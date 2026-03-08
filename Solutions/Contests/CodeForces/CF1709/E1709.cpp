#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
there was a very difficult to spot bug. im not sure why i didnt see it. 

when merging the children in small to large, there was a chance that the children would collide with each other. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int res = 0;
    vector<set<int>> dp(n);
    vector<int> x(n);

    auto dfs = [&](auto self, int i, int p) -> void {
        int maxc = -1;
        int f = 0;

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                if(maxc == -1 || sz(dp[c]) > sz(dp[maxc])) {
                    maxc = c;
                }
                if(dp[c].count(a[i] ^ x[c])) f = 1;
            }
        }

        if(maxc != -1) {
            swap(dp[i], dp[maxc]);
            x[i] = x[maxc]; 
        }

        for(int c : adj[i]) {
            if(c != p && c != maxc) {
                for(int s : dp[c]) {
                    if(dp[i].count(s ^ x[c] ^ x[i] ^ a[i])) f = 1;
                }
                for(int s : dp[c]) {
                    dp[i].insert(s ^ x[c] ^ x[i]);
                }
            }
        }

        dp[i].insert(x[i]);
        x[i] ^= a[i];

        if(f) {
            res++;
            dp[i].clear();
        }
    };

    auto dfs_slow = [&](auto self, int i, int p) -> void {
        int maxc = -1;
        int f = 0;

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                if(maxc == -1 || sz(dp[c]) > sz(dp[maxc])) {
                    maxc = c;
                }
                // cout << "i : " << i << " c : " << c << " set : " << dp[c] << endl;
                if(dp[c].count(a[i])) f = 1;
            }
        }

        if(maxc != -1) {
            for(int x : dp[maxc]) dp[i].insert(x);
        }

        for(int c : adj[i]) {
            if(c != p && c != maxc) {
                for(int s : dp[c]) {
                    if(dp[i].count(a[i] ^ s)) f = 1;
                }
                for(int s : dp[c]) {
                    dp[i].insert(s);
                }
            }
        }

        // cout << "i : " << i << " f : " << f << endl;

        if(f) {
            res++;
            dp[i].clear();
        } else {
            set<int> o;
            for(int x : dp[i]) o.insert(x ^ a[i]);
            o.insert(a[i]);
            swap(dp[i], o);
        }
    };

    dfs(dfs, 0, -1);
    // dfs_slow(dfs_slow, 0, -1);

    // for(int i = 0; i < n; i++) {
    //     int p = res;
    //     res = 0;
    //     dp.assign(n, {});
    //     dfs_slow(dfs_slow, 0, -1);
    //     assert(res == p);
    // }

    cout << res << '\n';

    return 0;
}