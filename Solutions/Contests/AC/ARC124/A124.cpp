#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<vector<bool>> v(n, vector<bool>(k,1));
    vector<int> visited(n,-1);
    bool poss = 1;
    for(int i = 0; i < k; i++) {
        char side; cin >> side;
        int dist; cin >> dist;
        if(side == 'L') {
            for(int j = 0; j < dist - 1; j++) {
                // cout << "set false : " << j << " " << i << '\n';
                v[j][i] = 0;
            }
            if(visited[dist-1] == -1) {
                visited[dist-1] = i;
            } else {
                poss = false;
            }
        }
        if(side == 'R') {
            dist = n - dist + 1;
            for(int j = n - 1; n - 1 - j < dist - 1; j--) {
                // cout << "set false : " << j << " " << i << '\n';
                v[j][i] = 0;
            }
            if(visited[n-dist] == -1) {
                visited[n-dist] = i;
            } else {
                poss = 0;
            }
        }
    }
    if(!poss) {
        cout << "not poss ?\n";
        cout << "0\n";
        return 0;
    }
    ll ans = 1;

    for(int i = 0; i < n; i++) {
        if(visited[i] != -1) continue;
        ll cnt = 0;
        for(int j = 0; j < k; j++) {
            cnt += v[i][j];
        }
        ans *= cnt;
        ans %= MOD;
    }
    cout << ans << '\n';
    return 0;
}