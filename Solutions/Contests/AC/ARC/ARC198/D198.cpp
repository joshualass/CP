#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<array<int,2>>> ch(n, vector<array<int,2>>(n));
    vector<vector<array<int,2>>> lens(n + 1); //length is the length of the path. 

    auto dfs = [&] (auto self, int l, int r, int len, int sec, int prev) -> void {

        // cout << "dfs l : " << l << " r : " << r << " len : " << len << " sec : " << sec << " prev : " << prev << '\n';

        ch[min(l,r)][max(l,r)] = {min(sec, prev), max(sec, prev)};
        //Just one time, dealer!
        if(l <= r) lens[len].push_back({l, r});

        for(int c : adj[r]) {
            if(c != prev) {
                if(len == 1) {
                    sec = c;
                }
                self(self, l, c, len + 1, sec, r);
            }
        }

    };

    for(int i = 0; i < n; i++) dfs(dfs, i, i, 1, i, i);

    dsubuild();

    vector<string> a(n);
    for(auto &x : a) cin >> x;

    for(int len = n; len; len--) {
        for(auto [l, r] : lens[len]) {
            if(a[l][r] == '1') {
                merge(l, r);
                if(len > 2) {
                    auto [chl, chr] = ch[l][r];
                    a[chl][chr] = '1';
                }
            }
        }
    }

    vector<vector<int>> ispal(n, vector<int>(n));

    int res = 0;

    for(int len = 1; len <= n; len++) {
        for(auto [l, r] : lens[len]) {
            int chpal;
            if(len <= 2) {
                chpal = 1;
            }  else {
                auto [chl, chr] = ch[l][r];
                chpal = ispal[chl][chr];
            }

            if(chpal && find(l) == find(r)) ispal[l][r] = 1;

            if(ispal[l][r]) res++;
        }
    }

    cout << res * 2 - n << '\n';

    return 0;
}
