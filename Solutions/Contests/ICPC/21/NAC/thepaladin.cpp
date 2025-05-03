#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    vector<vector<int>> dp((k + 1) / 2, vector<int>(26,1e9));
    for(int i = 0; i < 26; i++) dp[0][i] = 0;

    map<string,int> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int c; cin >> c;
        m[s] = c;
    }

    for(int i = 0; i < (k + 1) / 2 - 1; i++) {
        for(int j = 0; j < 26; j++) {
            for(int l = 0; l < 26; l++) {
                string f = "", r = "";
                f.push_back('a' + j);
                f.push_back('a' + l);
                r.push_back('a' + l);
                r.push_back('a' + j);
                if(m.count(f) && m.count(r)) {
                    dp[i+1][l] = min(dp[i+1][l], dp[i][j] + m[f] + m[r]);
                }
            }
        }
    }

    int res = 1e9;
    for(int i = 0; i < 26; i++) {
        if(k & 1) {
            res = min(res, dp[(k + 1) / 2 - 1][i]); 
        } else {
            string f = "";
            f.push_back('a' + i);
            f.push_back('a' + i);
            if(m.count(f)) res = min(res, dp[(k + 1) / 2 - 1][i] + m[f]);
        }
    }

    cout << (res < 1e9 ? res : -1) << '\n';

    return 0;
}
