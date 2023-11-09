#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    // for(auto &x : adj) {
    //     for(auto &y : x) os << y << " ";
    //     os << "\n";
    // }
    for(int i = 0; i < adj.size(); i++) {
        cout << "i: " << i << " --- " ;
        for(auto x : adj[i]) cout << x << " ";
        cout << '\n';
    }
    return os;
}

int dfs(int i, vector<vector<int>> &adj, vector<int> &dp) {
    int bestchild = 0;
    for(auto x : adj[i]) {
        if(dp[x] == -1) {
            dfs(x,adj,dp);
        }
        bestchild = max(bestchild,dp[x]);
    }
    dp[i] = bestchild + 1;
    return dp[i];
}

bool cycle(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &visiting) {
    if(visiting[i]) {
        return true;
    }
    if(visited[i]) {
        return false;
    }
    visiting[i] = true;
    for(auto x : adj[i]) {
        if(cycle(x,adj,visited,visiting)) {
            return true;
        }
    }
    visiting[i] = false;
    visited[i] = true;
    return false;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num > n) continue;

        int neededstartingidx = num - 1;
        //how many left shifts from beginning orientation do we need to get here?
        int shiftidx = (i + n - neededstartingidx) % n;
        //the next left-shift we will end at
        int nextshift = (shiftidx + num) % n; 
        adj[nextshift].push_back(shiftidx);
        // int start = num - 1;
        // int shift = (i + n - start) % n;
        // int nextshift = (shift + n - num) % n;
        // cout << "i: " << i << " shiftidx: " << shiftidx << " next shift: " << nextshift << '\n';
        // adj[nextshift].push_back(shift);

    }

    // cout << adj << '\n';

    vector<bool> visited(n);
    vector<bool> visiting(n);

    bool hascycle = cycle(0,adj,visited,visiting);
    // cout << "hascycle from start: " << hascycle << '\n';
    if(hascycle) {
        cout << "Yes\n";
        return;
    }
    vector<int> dp(n,-1);
    int longestpath = dfs(0, adj, dp) - 1;

    if(longestpath >= k) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    
    // if(ans == -1 || ans >= k) {
    //     cout << "Yes\n";
    // } else {
    //     cout << "No\n";
    // }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}