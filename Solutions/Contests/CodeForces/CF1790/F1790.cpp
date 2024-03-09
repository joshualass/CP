#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {

    

    // int n; cin >> n;
    // vector<bool> colored(n);
    // int c0; cin >> c0;
    // colored[c0-1] = 1;
    // vector<int> order(n-1);
    // for(int &x : order) cin >> x;
    // vector<vector<int>> adj(n);
    // for(int i = 0; i < n - 1; i++) {
    //     int a, b; cin >> a >> b;
    //     a--; b--;
    //     adj[a].push_back(b);
    //     adj[b].push_back(a);
    // }
    // int lo = INT_MAX;
    // vector<int> visited(n,-1);
    // for(int i = 0; i < n - 1; i++) {
    //     queue<array<int,3>> q;
    //     q.push({order[i]-1,-1,0});
    //     while(q.size()) {
    //         array<int,3> arr = q.front();
    //         q.pop();
    //         if(visited[arr[0]] == i) continue;
    //         if(colored[arr[0]]) {
    //             lo = arr[2];
    //             break;
    //         }
    //         visited[arr[0]] = i;
    //         if(rand() % 10 == 0) {
    //             random_shuffle(adj[arr[0]].begin(), adj[arr[0]].end());
    //         }
    //         for(int u : adj[arr[0]]) {
    //             if(arr[2] + 1 < lo && u != arr[1]) {
    //                 q.push({u,arr[0],arr[2]+1});
    //             }
    //         }
    //     }
    //     colored[order[i]-1] = 1;
    //     cout << lo << " \n"[i == n - 2];
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(chrono::steady_clock::now().time_since_epoch().count());
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}