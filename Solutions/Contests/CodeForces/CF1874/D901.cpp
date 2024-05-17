#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printAdj(const vector<vector<int>> &adj) {
    cout << "adj:\n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i: " << i << " -";
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

void solve() {
    int n; cin >> n;
    map<int,int> m;
    int prev = -1;
    int mex = -1;
    vector<int> v(n);
    for(auto& x: v) cin >> x;
    sort(v.begin(),v.end());
    for(int i = 0; i < n; i++) {
        int num = v[i];
        if(mex == -1 && num > prev + 1) {
            mex = prev + 1;
        }
        prev = num;
        if(mex == -1) {
            if(m.find(num) == m.end()) {
                m[num] = 1;
            } else {
                m[num]++;
            }
        }
    }
    if(mex == -1) mex = v.back() + 1;
    vector<int> removes(0);
    int prevsize = INT_MAX;
    for(pair<int,int> x : m) {
        if(x.second >= prevsize) {
            removes.push_back(x.first);
        }
        prevsize = min(prevsize,x.second);
    }
    for(auto x : removes) m.erase(x);
    // cout << "mex: " << mex << "\n";
    vector<vector<int>> dp(n+1,vector<int>(mex+1,INT_MAX));
    dp[0][mex] = 0;
    for(int i = 0; i <= n; i++) {
        int lo = INT_MAX;
        for(int j = 0; j <= mex; j++) {
            if(dp[i][j] < lo) {
                for(pair<int,int> x : m) {
                    if(x.first >= j) break;
                    dp[i+x.second][x.first] = min(dp[i+x.second][x.first], dp[i][j] + j * (x.second - 1) + x.first);
                }
            }
            lo = min(lo,dp[i][j]);
        }
    }
    // printAdj(dp);
    int ans = INT_MAX;
    for(int i = 0; i <= n; i++) {
        ans = min(ans,dp[i][0]);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}