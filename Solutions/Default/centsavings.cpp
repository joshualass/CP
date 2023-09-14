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

int round(int num) {
    if(num % 10 <= 4) {
        return num - num % 10;
    } else {
        return num + (10-num%10);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<int> v(n);
    for(int &x: v) cin >> x;
    vector<vector<int>> dp(n,vector<int>(d+1));
    for(int i = 0; i < n; i++) {
        for(int h = 0; h <= d; h++) {
            if(i != 0) {
                if(h == 0) {
                    dp[i][h] = dp[i-1][h] + v[i];
                } else {
                    dp[i][h] = min(dp[i-1][h] + v[i], round(dp[i-1][h-1])+v[i]);
                }
            } else {
                dp[i][h] = v[i];
            }
        }
    }    
    int least = INT_MAX;
    for(int h = 0; h <= d; h++) {
        least = min(round(dp[n-1][h]),least);
    }
    // printAdj(dp);
    cout << least << "\n";
    return 0;
}