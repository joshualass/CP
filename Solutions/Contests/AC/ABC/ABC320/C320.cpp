#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m; cin >> m;
    vector<string> v(3);
    for(auto &x : v) {cin >> x;
        x += x;
        x += x;
    }
    int ans = INT_MAX;
    for(int i = 0; i <= 9; i++) {
        vector<vector<int>> help(3);
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < v[j].size(); k++) {
                if(v[j][k] - '0' == i && help[j].size() < 3) {
                    help[j].push_back(k);
                }
            }
        }
        bool poss = true;
        for(auto x : help) {
            if(x.size() == 0) poss = false;
        }
        if(poss == false) continue;
        int best = INT_MAX;
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    if(help[0][j] == help[1][k] || help[0][j] == help[2][l] || help[1][k] == help[2][l]) continue;
                    best = min(best,max({help[0][j],help[1][k],help[2][l]}));
                }
            }
        }
        ans = min(ans,best);
    }
    if(ans == INT_MAX) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }


    return 0;
}