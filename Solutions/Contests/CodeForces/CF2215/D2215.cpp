#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 2; i < n; i++) {
        cin >> a[i];
    }

    vector<ll> suf(n + 1);
    for(int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i+1] + a[i];
    }

    // map<pair<array<int,2>,vector<int>>, ll> dp;
    vector dp(n, vector<map<int,ll>>(31));
    vector<int> vis(n);
    vis[0] = 1;
    vis[1] = 1;

    auto get_state = [&](int s, int w) -> array<int,3> {
        assert(abs(s - w) <= 15);
        int bm = 0;
        for(int i = min(s, w) + 1; i < max(s, w); i++) {
            if(vis[i]) bm += 1 << (i - (min(s, w) + 1));
        }
        return {s, w - s + 15, bm};
    };

    //can block if s is far ahead of w and the vis blocks w's steps
    auto can_block = [&](int s, int w) -> int {
        if(!(s > w)) return 0;
        int start_s = s;
        while(1) {
            s++;
            int f = 0;
            for(int j = 4; j >= 1; j--) {
                if(w + j < n && vis[w+j] == 0 && (w + j < start_s || w + j > s)) {
                    w += j;
                    f = 1;
                    break;
                }
            }
            if(f == 0) return 1;
            if(w > s) return 0;
        }
    };

    auto game_done = [&](int s, int w) -> int {
        for(int i = 1; i <= 4; i++) {
            if(s + i < n && vis[s + i] == 0) return 0;
            if(w + i < n && vis[w + i] == 0) return 0;
        }
        return 1;
    };

    auto dfs = [&](auto self, int s, int w) -> ll {
        auto [x, y, z] = get_state(s, w);
        
        if(!(0 <= x && x < n && 0 <= y && y < 31)) {
            cout << "s : " << s << " w : " << w << " vis : " << vis << " x : " << x << " y : " << y << " z : " << z << endl;
            assert(0);
        }

        if(dp[x][y].count(z)) return dp[x][y][z];

        ll res = -inf;
        if(game_done(s, w)) {
            res = 0;
        } else if(can_block(s, w)) {
            // cout << "s : " << s << " w : " << w << " vis : " << vis << endl;
            // cout << "it's all blocked up" << endl;
            ll score = suf[s + 1];
            assert(w < s);
            for(int i = w + 1; i < s; i++) {
                if(vis[i] == 0) score -= a[i];
            }
            res = score;
        } else {
            int f = 0;
            for(int i = 1; i <= 4; i++) {
                if(i + s < n && vis[i + s] == 0) {
                    vis[i + s] = 1;
                    ll to = -self(self, w, i + s);
                    vis[i + s] = 0;
                    // cout << "s : " << s << " w : " << w << " vis : " << vis << endl;
                    // cout << "i : " << i << " to : " << to << endl;
                    res = max(res, a[i + s] + to);
                    f = 1;
                }
            }
            if(f == 0) {
                res = -self(self, w, s);
            }
        }

        // cout << "s : " << s << " w : " << w << " vis : " << vis << endl;
        // cout << "res : " << res << endl;

        if(abs(res) >= inf) {
            cout << "too big res : " << res << endl;
            cout << "s : " << s << " w : " << w << endl;
            cout << "vis : " << vis << endl;
            assert(0);
        }
        dp[x][y][z] = res;
        return res;
    };

    dfs(dfs, 0, 1);

    auto [fx, fy, fz] = get_state(0, 1);

    cout << dp[fx][fy][fz] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}