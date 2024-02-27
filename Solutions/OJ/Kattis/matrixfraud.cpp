#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c; cin >> r >> c;
    vector<string> mat(r);
    for(string &s : mat) cin >> s;
    if(c > r) {
        vector<string> temp(c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                temp[j].push_back(mat[i][j]);
            }
        }
        swap(mat,temp);
        swap(r,c);
    }
    vector<vector<int>> dp(c,vector<int>(c));
    vector<vector<int>> prev(c,vector<int>(c));

    vector<int> prefone(c+1); //prefix sum for sum of 1's, 1-indexed
    vector<int> minrights(c); //minimum number operations needed such that the contiguous sequence of 1's ends at index i
    for(int i = 0; i < r; i++) {
        swap(prev,dp);
        prefone[0] = 0;
        for(int j = 0; j < c; j++) {
            prefone[j+1] = prefone[j] + (mat[i][j] == '1'); 
            minrights[j] = INT_MAX;
        }
        for(int l = 0; l < c; l++) {
            int curr_min = INT_MAX;
            if(l != 0) {
                curr_min = minrights[l-1];
            }
            for(int r = l; r < c; r++) {
                minrights[r] = min(minrights[r], prev[l][r]);
                curr_min = min(curr_min,minrights[r]);
                dp[l][r] = curr_min + (r - l + 1) - (prefone[r+1] - prefone[l]) + (prefone[l] - prefone[0]) + (prefone[c] - prefone[r+1]);
            }
        }
        if(i == 0) {
            for(int l = 0; l < c; l++) {
                for(int r = l; r < c; r++) {
                    if(l != 0) {
                        dp[l][r] = 1e9;
                    }
                }
            }
        }
    }

    int ans = INT_MAX;
    for(int l = 0; l < c; l++) {
        ans = min(ans, dp[l][c-1]);
    }
    cout << ans << '\n';
    return 0;
}