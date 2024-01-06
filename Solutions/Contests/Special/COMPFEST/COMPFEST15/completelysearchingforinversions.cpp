#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll MOD = 998244353;

template <typename T>
std::ostream& operator<<(std::ostream& os, const array<T,3> &arr) {
    // os << '(' << p.first << ", " << p.second << ") ";
    os << '[' << arr[0] << ", " << arr[1] << ", " << arr[2] << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<vector<pair<int,int>>> adj(n);
    vector<vector<int>> trans(n);
    vector<int> indegrees(n);
    for(int i = 0; i < n; i++) {
        int edgecnt; cin >> edgecnt;
        for(int edge = 0; edge < edgecnt; edge++) {
            int l, w; cin >> l >> w;
            l--;
            adj[i].push_back({l,w});
            trans[l].push_back(i);
            indegrees[l]++;
        }
    }

    queue<int> q;
    vector<int> top;
    
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }

    while(q.size()) {
        int i = q.front();
        q.pop();
        top.push_back(i);
        for(pair<int,int> p : adj[i]) {
            int edge = p.first;
            indegrees[edge]--;
            if(indegrees[edge] == 0) {
                q.push(edge);
            }
        }
    }

    // cout << "top : " << top << '\n';
    vector<array<ll,3>> dp(n); //dp[i] stores for node i {number of inversions on this node, number of zeroes on this node, number of ones}
    for(int i = n - 1; i >= 0; i--) {
        int node = top[i];
        ll inversions = 0;
        ll zeroes = 0;
        ll ones = 0;
        for(int j = adj[node].size() - 1; j >= 0; j--) {
            int to = adj[node][j].first;
            int val = adj[node][j].second;
            //adding dfs(to)
            inversions += dp[to][0] + dp[to][2] * zeroes;
            zeroes += dp[to][1];
            ones += dp[to][2];

            //adding edge of W i,j
            if(val == 0) {
                zeroes++;
            } else {
                ones++;
                inversions += zeroes;
            }
            inversions %= MOD;
            zeroes %= MOD;
            ones %= MOD;
        }
        dp[node] = {inversions, zeroes, ones};
        // cout << "i : " << i << " node : " << node << " dp[node] : " << dp[node] << '\n';
    }

    // cout << "dp : " << dp << '\n';

    cout << dp[top[0]][0] << '\n';

    return 0;
}