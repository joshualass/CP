#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int offset = 4e5;
int pre[20][offset + 1];
int dp[1 << 20];
int closed[20];
int cnts[20];
int inccnt[1 << 20];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int cnt = 0; //number of ) - number of (
        int mostopen = 0; //make sure count of ) after ( is >= 0
        int mostclosed = 0; //through all prefixes, maximum ) - (
        for(char c : s) {
            if(c == '(') {
                cnt--;
                mostopen++;
            } else {
                cnt++;
                mostopen = max(0,mostopen - 1);
            }
            if(mostopen == 0) {
                pre[i][cnt]++;
            }
            mostclosed = max(mostclosed, cnt);
        }
        closed[i] = mostclosed;
        cnts[i] = cnt * -1;
        // cout << "s : " << s << '\n';
        // cout << "p : ";
        // for(int j = 0; j < s.size(); j++) {
        //     cout << pre[i][j] << " ";
        // }
        // cout << '\n';
    }

    fill(begin(dp), end(dp), -1);

    dp[0] = 0;
    inccnt[0] = 0;

    int res = 0;
    for(int bm = 0; bm < 1 << n; bm++) {
        for(int use = 0; use < n; use++) {
            int prevbm = bm ^ (1 << use);
            if(dp[prevbm] != -1) {
                int cnt = dp[prevbm] + pre[use][inccnt[prevbm]];
                inccnt[bm] = inccnt[prevbm] + cnts[use];
                // cout << "bm : " << bm << " use : " << use << " prev bm : " << prevbm << " prev cnt : " << dp[prevbm] << " previnc ? " << inccnt[prevbm] << " adding : " << pre[use][inccnt[prevbm]] << " sum : " << cnt << '\n';
                res = max(res, cnt);
                if(closed[use] <= inccnt[prevbm]) {
                    dp[bm] = max(dp[bm], cnt);
                    // cout << "dp updated\n";
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}