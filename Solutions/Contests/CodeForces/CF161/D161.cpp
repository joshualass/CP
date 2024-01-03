#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[50000][501];
ll ans = 0;
int k;

void dfs(int i, int p, vector<vector<int>> &adj) {
    memset(dp[i],0,sizeof(dp[i]));
    dp[i][0] = 1;
    //first add to total score
    for(int child : adj[i]) {
        if(child != p) {
            dfs(child, i, adj);
            for(int j = 0; j < 500; j++) {
                dp[i][j+1] += dp[child][j];
            }
        }
    }
    //second add to score
    for(int child : adj[i]) {
        if(child != p) {
            for(int j = 0; j < k; j++) {
                if(j == k - 1) {
                    // cout << "i : " << i << " child : " << child << " j : " << j << " adding : " << dp[child][j] << '\n';
                    ans += dp[child][j] * 2;
                } else {
                    ans += dp[child][j] * (dp[i][k - j - 1] - dp[child][k - j - 2]);
                    // cout << "i : " << i << " child : " << child << " j : " << j << " adding : " << dp[child][j] * (dp[i][k - j - 1] - dp[child][k - j - 2]) << '\n';
                }

            }
        }
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n >> k;
    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0,-1,adj);

    cout << ans / 2 << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// struct Edge {
//     int v;
//     int dp[500];
//     Edge (int V) {
//         v = V;
//         memset(dp,0,sizeof(dp));
//     }
// };

// void dfs(int i, int edgeid, vector<vector<Edge>> &adj) {
//     int to = adj[i][edgeid].v;
//     for(int j = 0; j < adj[to].size(); j++) {
//         if(adj[to][j].v != i) {
//             if(adj[to][j].dp[0] == 0) {
//                 // dfs(adj[to][j].v, j, adj);
//                 dfs(to,j,adj);
//             }
//             for(int k = 0; k < 499; k++) {
//                 adj[i][edgeid].dp[k+1] += adj[to][j].dp[k];
//             }
//         }
//     }
//     adj[i][edgeid].dp[0] = 1;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, K; cin >> n >> K;
//     vector<vector<Edge>> adj(n);

//     for(int i = 0; i < n - 1; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         adj[a].push_back(Edge(b));
//         adj[b].push_back(Edge(a));
//     }

//     for(int k = 0; k < K; k++) {
//         for(int i = 0; i < n; i++) {
//             for(int j = 0; j < adj[i].size(); j++) {
                
//             }
//         }
//     }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < adj[i].size(); j++) {
    //         if(adj[i][j].dp[0] == 0) {
    //             dfs(i,j,adj);
    //         }
    //     }
    // }

    // ll ans = 0;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < adj[i].size(); j++) {
    //         ans += adj[i][j].dp[k-1];
    //     }
    // }
    // cout << ans / 2 << '\n';
    // return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// ll dfs(int i, int p, int step, int k, vector<vector<int>> &adj) {
//     if(step == k) return 1;
//     ll cnt = 0;
//     for(auto node : adj[i]) {
//         if(node != p) {
//             cnt += dfs(node, i, step + 1, k, adj);
//         }
//     }
//     return cnt;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, k; cin >> n >> k;

//     vector<vector<int>> adj(n);

//     for(int i = 0; i < n - 1; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//     }

//     ll cnt = 0;
//     for(int i = 0; i < n; i++) {
//         cnt += dfs(i, -1, 0, k, adj);
//     }

//     cout << cnt / 2 << '\n';

//     return 0;
// }