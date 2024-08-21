#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//we do not like using segment trees 

void solve() {
    int n; cin >> n;
    vector<int> f(n);
    vector<int> a(n);
    vector<int> vis(n,1);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = num - 1;
        f[num-1]++;
    }

    int hi = -1;
    int lo = -1;
    vector<int> res;

    priority_queue<array<int,2>> maxs; // {val, idx}
    priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> mins; // {val, idx}

    while(1) {
        // cout << "start hi : " << hi << '\n';
        while(hi != n - 1) {
            if(hi == -1 || vis[a[hi]] == 0 || f[a[hi]]) {
                hi++;
            } else {
                break;
            }
            maxs.push({a[hi],-hi});
            mins.push({a[hi],hi});
            f[a[hi]]--;
        }
        // cout << "hi stopping : " << hi << '\n';
        if(res.size() & 1) {
            while(mins.size() && (vis[mins.top()[0]] == 0 || lo >= mins.top()[1])) {
                mins.pop();
            }
            if(mins.empty()) {
                break;
            }
            res.push_back(mins.top()[0]);
            lo = mins.top()[1];
            vis[mins.top()[0]] = 0;
        } else {
            while(maxs.size() && (vis[maxs.top()[0]] == 0 || lo >= -maxs.top()[1])) {
                maxs.pop();
            }
            if(maxs.empty()) {
                break;
            }
            res.push_back(maxs.top()[0]);
            lo = -maxs.top()[1];
            vis[maxs.top()[0]] = 0;
        }
    }
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] + 1 << " \n"[i == res.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}