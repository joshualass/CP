#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int maxdoubles(string s, int t) {
    int doubles = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == t + '0' && s[i-1] == t + '0') {
            doubles++;
            i++;
        }
    }
    return min((int) s.size() / 4, doubles);
}

int greedy(string s) {
    int cnt = 0;
    int doublesleft = s.size() / 4;
    int singlesleft = s.size() / 2;
    vector<int> vis(s.size());
    for(int i = 0; i + 1 < s.size(); i++) {
        if(s[i] != s[i+1] && doublesleft && vis[i] == 0 && vis[i+1] == 0) {
            doublesleft--;
            vis[i] = 1;
            vis[i+1] = 1;
            cnt++;
        }
    }
    for(int i = 0; i + 1 < s.size(); i++) {
        if(s[i] == '0' && s[i+1] == '0' && doublesleft && vis[i] == 0 && vis[i+1] == 0) {
            doublesleft--;
            vis[i] = 1;
            vis[i+1] = 1;
        }
    }
    for(int i = 0; i + 1 < s.size(); i++) {
        if(s[i] == '1' && s[i+1] == '1' && doublesleft && vis[i] == 0 && vis[i+1] == 0) {
            doublesleft--;
            cnt++;
            vis[i] = 1;
            vis[i+1] = 1;
        }
    }
    for(int i = 0; i < s.size(); i++) {
        if(vis[i] == 0) {
            cnt += s[i] == '1';
        }
    }
    return cnt;
}

int dp(string s) {
    vector<vector<vector<int>>> dp(s.size() + 1, vector<vector<int>>(s.size() / 2 + 1, vector<int>(s.size() / 4 + 1)));

    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j <= s.size() / 2; j++) {
            for(int k = 0; k <= s.size() / 4; k++) {
                if(j != s.size() / 2) {
                    dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k] + (s[i] == '1'));
                }
                if(i + 1 < s.size() && k != s.size() / 4) {
                    dp[i+2][j][k+1] = max(dp[i+2][j][k+1], dp[i][j][k] + (s[i] == '1' || s[i+1] == '1'));
                }
            }
        }
    }
    return dp.back().back().back();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 1 << 12; i++) {
        string s = "";
        for(int j = 0; j < 12; j++) {
            if(i & (1 << j)) {
                s.push_back('1');
            } else {
                s.push_back('0');
            }
        }
        if(dp(s) != greedy(s)) {
            cout << "s : " << s << " dp : " << dp(s) << " greedy : " << greedy(s) << '\n';
            return 0;
        }
    }
    
    // int n, m; cin >> n >> m;
    // int lo = 0, hi = 0;
    // for(int i = 0; i < n; i++) {
    //     string s; cin >> s;
    //     int countzero = count(s.begin(), s.end(), '0');
    //     int countone = count(s.begin(),s.end(), '1');
    //     lo += countone - maxdoubles(s,1); //find min that can be occupied
    //     hi += greedy(s);
    // }

    // cout << lo << " " << hi << '\n';

    return 0;
}