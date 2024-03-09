#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<int>> revs(n);
    vector<int> outgoings(n);
    outgoings[n-1] = 1e9;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if(a == n || b == 1) continue; //ignore unnecessary edges
        a--; b--;
        adj[a].push_back(b);
        revs[b].push_back(a);
        outgoings[a]++;
    }

    vector<pair<int,int>> dp(n, {-1,-1});
    dp[n-1] = {1, -1};

    for(auto x : revs[n-1]) {
        outgoings[x]--;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(outgoings[i] == 0) {
            q.push(i);
        }
    }

    while(q.size()) {
        int num = q.front();
        // cout << "num: " << num << '\n';
        q.pop();
        for(auto x : adj[num]) {
            if(dp[x].first != -1) {
                if(dp[num].first <= dp[x].first) {
                    dp[num] = {dp[x].first + 1, x};
                }
            }
        }
        for(auto x : revs[num]) {
            outgoings[x]--;
            if(outgoings[x] == 0) {
                q.push(x);
            }
        }

    }

    if(dp[0].first == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << dp[0].first << "\n";
        int curr = 0;
        while(curr != -1) {
            cout << curr+1 << " ";
            curr = dp[curr].second;
        }
    }

    return 0;
}