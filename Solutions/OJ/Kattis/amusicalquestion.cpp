#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1000;

int dp[N + 1][N + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int c, n; cin >> c >> n;

    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    int a = -1, b = -1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        for(int j = c; j >= 0; j--) {
            for(int k = j; k >= 0; k--) {
                if(dp[j][k]) {
                    a = j + num;
                    b = k;
                    if(a <= c) {
                        dp[a][b] = 1;
                    }
                    a = j;
                    b = k + num;
                    if(b <= c) {
                        if(b > a) {
                            swap(a,b);
                        }
                        dp[a][b] = 1;
                    }
                }
            }
        }
    }

    pair<int,int> ans = {0,0};
    for(int i = 0; i <= c; i++) {
        for(int j = 0; j <= c; j++) {
            if(dp[i][j]) {
                if(i + j > ans.first + ans.second || i + j == ans.first + ans.second && i - j < ans.first - ans.second) {
                    ans = {i,j};
                }
            }
        }
    }
    cout << ans.first << " " << ans.second << '\n';

    return 0;
}