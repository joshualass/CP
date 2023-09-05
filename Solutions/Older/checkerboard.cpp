#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll incre(ll val, ll inc) {
    return val % 2 == inc ? val : ++val;
}

ll fill(vector<vector<ll>> mat, ll zero, ll one) {
    ll ans = 0;
    for (ll r = 0; r < mat.size(); r++) {
        for (ll c = 0; c < mat[0].size(); c++) {
            ll rprev = 0;
            ll cprev = 0;
            if (r != 0) {
                rprev = mat[r - 1][c];
            }
            if (c != 0) {
                cprev = mat[r][c - 1];
            }
            if (mat[r][c] == 0) {
                if ((r + c) % 2 == 0) {  // zero active
                    if (r % 2 == 0) {
                        mat[r][c] = incre(max(rprev, cprev) + 1, zero);
                    } else {
                        mat[r][c] = incre(max(rprev, cprev) + 1, zero ^ 1);
                    }
                } else {  // one active
                    if (r % 2 == 0) {
                        mat[r][c] = incre(max(rprev, cprev) + 1, one);
                    } else {
                        mat[r][c] = incre(max(rprev, cprev) + 1, one ^ 1);
                    }
                }
            } else {
                if (mat[r][c] <= rprev || mat[r][c] <= cprev) {
                    return -1;
                }
            }
            ans += mat[r][c];
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll r, c;
    cin >> r >> c;

    ll zero = -1;
    ll one = -1;

    if(r == 1 || c == 1) {
        ll size = max(r, c);
        ll ans = 0;
        ll prev = 0;
        for(int i = 0; i < size; i++) {
            ll num;
            cin >> num;
            if(num == 0) {
                prev += 1;
            } else {
                if(num <= prev) {
                    cout << "-1";
                    return 0;
                }
                prev = num;
            }
            ans += prev;
        }
        cout << ans;
        return 0;
    }

    vector<vector<ll>> mat(r, vector<ll>(c, 0));
    for (ll i = 0; i < r; i++) {
        for (ll t = 0; t < c; t++) {
            cin >> mat[i][t];
            if (mat[i][t] != 0) {
                if ((i + t) % 2 == 0) {  // zero cell
                    if (i % 2 == 0) {
                        if (zero != mat[i][t] % 2 && zero != -1) {
                            cout << "-1";
                            return 0;
                        }
                        zero = mat[i][t] % 2;
                    } else {
                        if (zero == mat[i][t] % 2 && zero != -1) {
                            cout << "-1";
                            return 0;
                        }
                        zero = (mat[i][t] % 2) ^ 1;
                    }
                } else {
                    if (i % 2 == 0) {
                        if (one != mat[i][t] % 2 && one != -1) {
                            cout << "-1";
                            return 0;
                        }
                        one = mat[i][t] % 2;
                    } else {
                        if (one == mat[i][t] % 2 && one != -1) {
                            cout << "-1";
                            return 0;
                        }
                        one = (mat[i][t] % 2) ^ 1;
    }}}}}

    if (zero == -1 && one == -1) {
        cout << min(fill(mat, 1, 0), fill(mat, 1, 1));
    } else if (zero == -1) {
        cout << min(fill(mat, 0, one), fill(mat, 1, one));
    } else if (one == -1) {
        cout << min(fill(mat, zero, 0), fill(mat, zero, 1));
    } else {
        cout << fill(mat, zero, one);
    }
}