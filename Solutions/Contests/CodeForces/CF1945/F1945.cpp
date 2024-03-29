#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &x : a) cin >> x.second;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[--num].first = i;
    }
    sort(a.begin(), a.end());

    priority_queue<ll, vector<ll>, greater<ll>> used;
    priority_queue<ll> unused;
    pair<ll,ll> ans = {-1,-1};
    for(int i = n - 1; i >= 0; i--) {
        unused.push(a[i].second);
        while(used.size() < i + 1 && unused.size()) {
            used.push(unused.top());
            unused.pop();
        }
        while(used.size() > i + 1) {
            unused.push(used.top());
            used.pop();
        }
        while(used.size() == i + 1 && unused.size() && used.top() < unused.top()) {
            ll c1 = used.top();
            ll c2 = unused.top();
            used.pop();
            used.push(c2);
            unused.pop();
            unused.push(c1);
        }
        if(used.size() == i + 1 && used.top() * (i + 1) >= ans.first) {
            ans = {used.top() * (i + 1),i+1};
        }
    }
    cout << ans.first << " " << ans.second << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}