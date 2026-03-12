#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

struct frac {
    ll n, d;
    frac(): n(0), d(0) {}
    frac(ll n, ll d): n(n), d(d) {}
    bool operator<(const frac& rhs) const {
        return n * rhs.d < d * rhs.n;
    }
    bool operator>(const frac& rhs) const {
        return n * rhs.d > d * rhs.n;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<frac> best(n);
    vector<priority_queue<frac, vector<frac>, greater<frac>>> dp(n);

    auto dfs = [&](auto self, int i) -> void {
        int maxc = -1;
        for(int c : ch[i]) {
            self(self, c);
            if(maxc == -1 || sz(dp[c]) > sz(dp[maxc])) maxc = c;
        }
        if(maxc != -1) swap(dp[i], dp[maxc]);
        for(int c : ch[i]) {
            if(c != maxc) {
                while(!dp[c].empty()) {
                    dp[i].push(dp[c].top());
                    dp[c].pop();
                }
            }
        }
        best[i].n = a[i];
        best[i].d = 1;
        while(sz(dp[i]) && dp[i].top() < best[i]) {
            best[i].n += dp[i].top().n;
            best[i].d += dp[i].top().d;
            dp[i].pop();
        }
        dp[i].push(best[i]);
    };

    dfs(dfs, 0);

    priority_queue<pair<frac,int>, vector<pair<frac,int>>, greater<pair<frac,int>>> pq;
    pq.push({best[0], 0});

    ll res = 0;
    int oc = 0;
    while(pq.size()) {
        auto [f, idx] = pq.top();
        pq.pop();
        if(a[idx] == 0) {
            res += oc;
        } else {
            oc++;
        }
        for(int c : ch[idx]) pq.push({best[c], c});
    }

    cout << res << '\n';

    return 0;
}
