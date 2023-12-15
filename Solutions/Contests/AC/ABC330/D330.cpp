#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<string> board(n);
    vector<ll> rowcnts(n);
    vector<ll> colcnts(n);

    for(int i = 0; i < n; i++) {
        cin >> board[i];
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'o') {
                rowcnts[i]++;
                colcnts[j]++;
            }
        }
    }

    ll ans = 0;

    for(int i = 0; i < n; i++) {
        // ll outside = totalcnt - rowcnts[i];
        // ans += outside * (max(rowcnts[i] - 1, 0LL)); 
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 'o') {
                ans += (rowcnts[i] - 1) * (colcnts[j] - 1);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}