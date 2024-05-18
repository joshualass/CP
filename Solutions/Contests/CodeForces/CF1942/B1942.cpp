#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<bool> vis(n);
    int mex = 0;
    set<int> unused;
    for(int i = 0; i < n; i++) {
        unused.insert(i);
    }
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num > 0) {
            cout << *unused.begin() << " \n"[i == n - 1];
            vis[*unused.begin()] = 1;
            unused.erase(unused.begin());
        } else {
            cout << mex - num << " \n"[i == n - 1];
            vis[mex-num] = 1;
            unused.erase(mex - num);
        }
        while(mex != n && vis[mex]) {
            mex++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}