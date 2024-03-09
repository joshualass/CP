#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

vector<int> cyclesizes(2);

void dfs1(int i, vector<int> &v, vector<int> &visited) {
    if(i < 0 || i >= visited.size()) {
        return;
    }
    if(visited[i] == -1) {
        visited[i] = 0;
        dfs1(i + v[i], v, visited);
        if(visited[i] == 0) {
            visited[i] = 1;
        }
    } else if(visited[i] == 0) {
        visited[i] = cyclesizes.size();
        cyclesizes.back()++;
        dfs1(i + v[i], v, visited);
    } else if(visited[i] == cyclesizes.size()) {
        cyclesizes.push_back(0);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);

    for(int &x : v) cin >> x;

    vector<int> visited(n,-1); // -1 - unvisited, 0 - visiting, 1 - done visiting

    for(int i = 0; i < n; i++) {
        if(visited[i] == -1) {
            dfs1(i, v, visited);
        }
    }

    // cout << "visited : " << visited << '\n';
    // cout << "cyclesizes : " << cyclesizes << "\n";

    vector<vector<int>> revadj(n);
    vector<int> indegrees(n);
    for(int i = 0; i < n; i++) {
        int next = i + v[i];
        if(next >= 0 && next < n && visited[i] == 1) {
            revadj[i + v[i]].push_back(i);
            indegrees[i]++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }

    ll ans = 0;
    vector<int> dp(n);

    while(q.size()) {
        int i = q.front();
        q.pop();
        if(visited[i] != 1) {
            int size = cyclesizes[visited[i] - 1];
            dp[i] = size;
        } else if(i + v[i] < 0 || i + v[i] >= n) {
            dp[i] = 1;
        }
        // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
        ans += dp[i];
        for(int v : revadj[i]) {
            q.push(v);
            dp[v] = dp[i]+1;
        }
    }
    cout << "dp : " << dp << '\n';
    cout << ans << '\n';
    return 0;
}