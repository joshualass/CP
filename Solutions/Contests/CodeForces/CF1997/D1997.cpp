#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll dfs(int i, vector<ll> &a, vector<vector<int>> &children) {

    if(children[i].size()) {
        ll minchild = LLONG_MAX;
        for(int c : children[i]) {
            minchild = min(minchild, dfs(c, a, children));
        }
        if(i == 0) {
            return a[i] + minchild;
        } else {
            if(a[i] < minchild) {
                return (a[i] + minchild) / 2;
            } else {
                return minchild;
            }
        }
    } else {
        return a[i];
    }

}

void solve() {
    int n; cin >> n;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> children(n);

    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        children[p].push_back(i);
    }

    cout << dfs(0,a,children) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}