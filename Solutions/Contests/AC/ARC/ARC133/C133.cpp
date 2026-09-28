#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool isvalid(vector<ll> rows, vector<ll> cols, ll k) {
    ll rowscore = reduce(rows.begin(),rows.end());
    ll colscore = reduce(cols.begin(),cols.end());
    return rowscore % k == colscore % k;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll R, C, K; cin >> R >> C >> K;

    vector<ll> r(R);
    vector<ll> c(C);

    for(auto &x: r) cin >> x;
    for(auto &x: c) cin >> x;

    // sort(r.rbegin(),r.rend());
    sort(r.begin(), r.end(), [C, K] (const ll &lhs, const ll &rhs) -> bool {
        ll lhs_leftover = (lhs + K - ((C - 1) * (K - 1) % K)) % K;
        ll rhs_leftover = (rhs + K - ((C - 1) * (K - 1) % K)) % K;
        return lhs_leftover > rhs_leftover;
    });

    sort(c.begin(), c.end(), [R, K] (const ll &lhs, const ll &rhs) -> bool {
        ll lhs_leftover = (lhs + K - ((R - 1) * (K - 1) % K)) % K;
        ll rhs_leftover = (rhs + K - ((R - 1) * (K - 1) % K)) % K;
        return lhs_leftover > rhs_leftover;
    });

    // for(auto x : r) cout << x << " ";
    // cout << '\n';

    if(!isvalid(r,c,K)) {
        cout << "-1\n";
        return 0;
    }

    ll ans = 0;
    ll remainder = 0;

    for(int i = 0; i < R - 1; i++) { //fill rows :)
        ll rowscore = (C - 1) * (K - 1);
        ans += rowscore;
        ll targetvalue = r[i] + K;
        ll leftover = (targetvalue - (rowscore % K)) % K;
        ans += leftover;
        remainder += leftover;
        // cout << "row: " << i << " rowscore: " << rowscore << " leftover: " << leftover << '\n';
    }
    for(int i = 0; i < C - 1; i++) { // fill cols >:
        ll colscore = (R - 1) * (K - 1);
        ll targetvalue = c[i] + K;
        ll leftover = (targetvalue - (colscore % K)) % K;
        ans += leftover;
        // cout << "col: " << i << " colscore: " << colscore << " leftover: " << leftover << '\n';
    }

    //last corner at the bottom right of matrix

    ll lastleftover = (c.back() + K * MOD - remainder % K) % K;

    // cout << "final supper: " << lastleftover << '\n';
    ans += lastleftover;

    cout << ans - K << '\n';

    return 0;
}