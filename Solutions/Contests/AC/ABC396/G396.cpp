#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
need some more practice with bm dp ...
What we want to compute 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int dp[19][19][1 << 18];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w; cin >> h >> w;
    vector<int> a(h), b(h);
    for(int i = 0; i < h; i++) {
        string s; cin >> s;
        int x = 0;
        for(int j = 0; j < w; j++) {
            x *= 2;
            x += s[j] - '0';
        }
        a[i] = x;
        b[i] = (x ^ ((1 << w) - 1));
    }

    // cout << "a : " << a << '\n';
    // cout << "b : " << b << '\n';

    vector<int> res(1 << w);

    auto add_scores = [&](vector<int> cnts, int s) -> void {
        memset(dp, 0, sizeof(dp));
        for(int x : cnts) dp[w][0][x]++;

        for(int i = w; i > 0; i--) { //last bit toggled, next to toggle is (i - 1)
            for(int j = 0; j < w; j++) { //number of toggles before
                for(int k = 0; k < 1 << w; k++) { //current bm
                    //no toggle
                    dp[i - 1][j][k] += dp[i][j][k];
                    //toggle
                    dp[i-1][j+1][k ^ (1 << (i - 1))] += dp[i][j][k];
                }
            }
        }

        for(int i = 0; i <= s; i++) {
            for(int j = 0; j < 1 << w; j++) {
                res[j] += (w - i) * dp[0][i][j];
            }
        }

    };

    add_scores(a, w / 2);

    // for(int i = 0; i < 1 << w; i++) cout << "i : " << i << " res[i] : " << res[i] << '\n';

    add_scores(b, (w - 1) / 2);

    // for(int i = 0; i < 1 << w; i++) cout << "i : " << i << " res[i] : " << res[i] << '\n';

    cout << h * w - (*max_element(res.begin(), res.end())) << '\n';

    return 0;
}