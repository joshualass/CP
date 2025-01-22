#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y, x0, y0; cin >> x >> y >> x0 >> y0;
    string s; cin >> s;
    
    vector vis(x,vector<int>(y));
    vector<int> res(s.size() + 1);

    x0--; y0--;
    vis[x0][y0] = 1;
    res[0] = 1;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'U') {
            x0 = max(x0 - 1,0);
        } else if(s[i] == 'D') {
            x0 = min(x0 + 1, x - 1);
        } else if(s[i] == 'L') {
            y0 = max(y0 - 1, 0);
        } else {
            y0 = min(y0+1,y-1);
        }
        if(vis[x0][y0] == 0) {
            vis[x0][y0] = 1;
            res[i+1]++;
        }
    }

    res.back() += (x * y - accumulate(res.begin(), res.end(), 0));

    for(int i = 0; i <= s.size(); i++) {
        cout << res[i] << " \n"[i == s.size()];
    }

    return 0;
}