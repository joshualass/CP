#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dp[1 << 16][15];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < 1 << 16; i++) {
        for(int j = 0; j < 15; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    int n; cin >> n;
    string s; cin >> s;

    int start = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') {
            start += 1 << i;
        }
    }

    queue<array<int,3>> q;
    q.push({start,n,0});

    while(q.size()) {
        auto [i, j, step] = q.front();
        q.pop();

        if(dp[i][j] != INT_MAX) continue;
        dp[i][j] = step;

        for(int move = 0; move < n+1; move++) {
            if(j + 1 < move || j > move + 1) {
                int to = i;

                int stones = (i >> move) & 3;
                to -= stones << move;
                to += stones << j;

                if(dp[to][move] == INT_MAX) {
                    q.push({to,move,step + 1});
                }

            }
        }
    }

    cin >> s;
    int end = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') end += 1 << i;
    }

    // int res = INT_MAX;
    // for(int i = 0; i < 1 << 16; i++) {
    //     for(int j = 0; j < 15; j++) {
    //         int after = i >> (j + 2);
    //         int to = i - (after << (j + 2)) + (after << j);
    //         if(to == end) {
    //             res = min(res,dp[i][j]);
    //         }
    //     }
    // }

    int res = dp[end][n];

    if(res == INT_MAX) {
        cout << "-1\n";
    } else {
        cout << res << '\n';
    }

    return 0;
}