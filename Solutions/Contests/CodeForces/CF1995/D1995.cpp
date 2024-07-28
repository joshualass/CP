#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//bitset too slow :( ?

const int MAXN = 18;
bitset<(1 << MAXN)> bs[MAXN];
bitset<(1 << MAXN)> use[MAXN + 1];

void dfs(int mask, vector<bool> &vis, int &res, int n, int c) {

    vis[mask] = 1;
    int sb = __builtin_popcount(mask);
    if(use[sb].count() == n) {
        res = min(res, sb);
        return;
    }

    for(int i = 0; i < c; i++) {
        if((mask & (1 << i)) == 0 && vis[mask | (1 << i)] == 0) {
            use[sb + 1] = bs[i] | use[sb];
            dfs(mask + (1 << i), vis, res, n, c);
        }
    }


}

void solve() {
    int n, c, k; cin >> n >> c >> k;
    string s; cin >> s;

    for(int i = 0; i < c; i++) {
        bs[i].reset();
    }

    for(int i = 0; i < n; i++) {
        int c = s[i] - 'A';
        for(int j = 0; j < k && i - j >= 0 && bs[c][i-j] == 0; j++) {
            bs[c][i-j] = 1;
        }
    }

    int mustusebit = s.back() - 'A';
    int res = INT_MAX;
    vector<bool> vis(1 << c);

    use[1] = bs[mustusebit];
    dfs(1 << mustusebit, vis, res, n, c);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}