// https://oj.uz/problem/view/NOI18_knapsack
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int s, n; cin >> s >> n;
    vector<vector<pair<int,int>>> items(s+1);

    for(int i = 0; i < n; i++) {
        int v, w, k; cin >> v >> w >> k;
        items[w].push_back({v,k});
    }
    //for each weight, store the maximum weight taking 1-n items
    vector<vector<int>> weights(s+1, vector<int>(s+1));
    for(int i = 1; i <= s; i++) {
        sort(items[i].begin(),items[i].end());
        for(int j = 1; j <= s && items[i].size(); j++) {
            weights[i][j] = weights[i][j-1] + items[i].back().first;
            items[i].back().second--;
            if(items[i].back().second == 0) items[i].pop_back();
        }
    }
    // cout << "weights: " << endl;
    // cout << weights << "\n";
    vector<vector<int>> dp(s + 1, vector<int>(s+1));

    for(int i = 1; i <= s; i++) {//trying weight i
        for(int j = 1; j <= s; j++) {//trying with current shopping cart weight j
            dp[i][j] = dp[i-1][j];
            for(int k = 1; j - k * i >= 0; k++) { //taking k items
                dp[i][j] = max(dp[i][j], dp[i-1][j - k * i] + weights[i][k]);
            }

        }
    }
    // cout << "dp\n";
    // cout << dp << "\n";
    cout << *max_element(dp[s].begin(),dp[s].end()) << "\n";
    return 0;
}