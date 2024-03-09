#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(1) {
        string s;
        getline(cin,s);
        if(cin.eof()) break;
        stringstream ss(s);
        int n, m; ss >> n >> m;
        vector<int> vals(m);
        for(int &x : vals) ss >> x;
        vector<bool> dp(n + 1); //dp[i] = 1 when it's possible to when on this turn, dp[i] = 0 if losing
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < m; j++) {
                if(i - vals[j] >= 0 && dp[i - vals[j]] == 0) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        cout << (dp[n] ? "Stan wins" : "Ollie wins") << '\n';
    }

    return 0;
}