#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    deque<int> q;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        q.push_back(num);
    }
    vector<int> order;
    string s; cin >> s;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'L') {
            order.push_back(q.front());
            q.pop_front();
        } else {
            order.push_back(q.back());
            q.pop_back();
        }
    }
    int p = 1;
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        p *= order[n-i-1];
        p %= m;
        ans.push_back(p);
    }
    reverse(ans.begin(), ans.end());
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}