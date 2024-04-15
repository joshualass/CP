#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool vis[20];

void do_op(int l, int r, vector<pair<int,int>> &ops, vector<int> &a) {
    memset(vis,0,sizeof(vis));
    for(int i = l; i <= r; i++) {
        vis[a[i]] = 1;
    }
    int val = -1;
    for(int i = 0; i < 20; i++) {
        if(vis[i] == 0) {
            val = i;
            break;
        }
    }
    for(int i = l; i <= r; i++) {
        a[i] = val;
    }
    ops.push_back({l,r});
}

void recur(int start, int curr, vector<pair<int,int>> &ops, vector<int> &a) {

    int needed = curr - start;

    if(start != curr) {
        recur(start, curr-1, ops, a);
    }
    if(a[curr] != needed) {
        do_op(start, curr, ops, a);
    }
    if(start != curr) {
        recur(start, curr-1, ops, a);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<pair<int,int>> dp(n);
    dp[0] = {a[0], -1};
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j >= -1; j--) {
            int v1 = (j == -1 ? 0 : dp[j].first);
            int v2 = (j == i - 1 ? a[i] : 0);
            int v = max((i - j) * (i - j), v2) + v1;
            if(v > dp[i].first) {
                dp[i] = {v, j};
            }
        }
    }

    vector<pair<int,int>> ops;
    int curr = n - 1;
    while(curr != -1) {
        // cout << "curr : " << curr << " dp[curr] : " << dp[curr].first << " " << dp[curr].second << '\n';
        int next = dp[curr].second;
        if(curr - next == 1 && a[curr] >= 1) {
            curr = next;
            continue;
        }
        recur(next + 1, curr, ops, a);
        ops.push_back({next+1,curr});
        curr = next;
    }

    cout << dp.back().first << " " << ops.size() << '\n';
    for(auto op : ops) {
        cout << op.first + 1 << " " << op.second + 1 << '\n';
    }

    return 0;
}