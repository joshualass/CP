#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
tree dp :(
*/

void tree_dp(int i, vector<vector<int>> &children, vector<vector<int>> &dp, int &ans, string &types) {
    if(types[i] == 'P') {
        for(int child : children[i]) {
            tree_dp(child,children,dp,ans,types);
            ans += min({dp[child][0], dp[child][1] + 1, dp[child][2]});
        }
        dp[i] = {0,1,1};
    }
    if(types[i] == 'S') {
        for(int child : children[i]) {
            tree_dp(child,children,dp,ans,types);
            ans += min({dp[child][0] + 1, dp[child][1], dp[child][2]});
        }
        dp[i] = {1,0,1};
    }
    if(types[i] == 'C') {
        int cntP = 0, cntS = 0, cntC = 0;
        for(int child : children[i]) {
            tree_dp(child,children,dp,ans,types);
            cntP += min({dp[child][0], dp[child][1] + 1, dp[child][2]});
            cntS += min({dp[child][0] + 1, dp[child][1], dp[child][2]});
            cntC += min({dp[child][0] + 1, dp[child][1] + 1, dp[child][2]});
        }
        dp[i] = {cntP,cntS,cntC};
    }

}

void solve() {
    int n; cin >> n;
    vector<vector<int>> childrens(n);
    for(int i = 1; i < n; i++) {
        int parent; cin >> parent;
        parent--;
        childrens[parent].push_back(i);
    }
    string types; cin >> types;
    int ans = 0;
    vector<vector<int>> dp(n,vector<int>(3)); // {min gates placed so that the subtree has party, min gates placed so that the subtree has sleep, min gates placed so that the subtree has care}
    tree_dp(0,childrens,dp,ans,types);        // {P,S,C}
    cout << ans + *min_element(dp[0].begin(), dp[0].end()) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}