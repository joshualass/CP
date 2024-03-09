#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printAdj(const vector<vector<int>> &adj) {
    cout << " --- adjlist --- \n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i - " << i << ':';
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<vector<int>> dp(n+1,vector<int>(x+1));
    vector<pair<int,int>> books(n);
    for(auto &x: books) cin >> x.first;
    for(auto &x: books) cin >> x.second;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= x; j++) {
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if(j - books[i-1].first >= 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j - books[i-1].first] + books[i-1].second);
            }
        }
    }
    cout << dp[n][x] << "\n";
    // printAdj(dp);
    return 0;
}