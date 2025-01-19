#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef array<ld, 2> vec2;

ld epsilon = 1e-10;

ll dist_sq(vec2 v0, vec2 v1) {return pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1], 2);}
ld dist(vec2 v0, vec2 v1) {
    return sqrt(dist_sq(v0, v1));
}

bool pt_on_line(vec2 v0, vec2 v1, vec2 pt) {
    // cout << "PT ON LINE : " << v0[0] << " " << v0[1] << " " << v1[0] << " " << v1[1] << " " << abs(dist(v0, v1) - dist(v0, pt) - dist(v1, pt)) << "\n";
    return abs(dist(v0, v1) - dist(v0, pt) - dist(v1, pt)) < epsilon;
}

vec2 sub(vec2 v0, vec2 v1) {
    return {v0[0] - v1[0], v0[1] - v1[1]};
}

vec2 add(vec2 v0, vec2 v1) {
    return {v0[0] + v1[0], v0[1] + v1[1]};
}

ld cross(vec2 a, vec2 b) {
    return a[0] * b[1] - a[1] * b[0];
}

ld tri_area(vec2 v0, vec2 v1, vec2 v2) {
    vec2 a = sub(v1, v0), b = sub(v2, v0);
    return abs(cross(a, b) / 2.0);
}

bool pt_in_tri(vec2 v0, vec2 v1, vec2 v2, vec2 pt) {
    v0 = sub(v0, pt), v1 = sub(v1, pt), v2 = sub(v2, pt);
    vec2 orig = {0, 0};
    ld area = tri_area(v0, v1, v2);
    ld test = tri_area(orig, v0, v1) + tri_area(orig, v1, v2) + tri_area(orig, v2, v0);
    // cout << "TEST : " << area << " " << test << "\n";
    return abs(area - test) < epsilon;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1];
    }
    vec2 b0, b1;
    cin >> b0[0] >> b0[1] >> b1[0] >> b1[1];
    vector<vector<bool>> legal(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n - 1; j++){
            if(!pt_on_line(a[i], a[(i + j) % n], b0) && !pt_on_line(a[i], a[(i + j) % n], b1)) legal[i][(i + j) % n] = true;
        }
    }
    vector<vector<ld>> dst(n, vector<ld>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) dst[i][j] = dist(a[i], a[j]);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(legal[i][j]) legal[j][i] = true;
        }
    }
    vector<vector<ld>> dpa(n, vector<ld>(n, 1e18)), dpb(n, vector<ld>(n, 1e18));
    vector<vector<ld>> dp(n, vector<ld>(n, 1e18));  //inclusive
    //base case
    for(int i = 0; i < n; i++) {
        dp[i][(i + 1) % n] = 0;
    }
    for(int i = 2; i < n; i++) {
        for(int j = 0; j < n; j++){
            int l = j, _r = j + i, r = _r % n;
            for(int _k = l + 1; _k < _r; _k++){
                int k = _k % n;
                if(!legal[l][k] || !legal[k][r]) continue;
                // cout << "LEGAL : " << l << " " << k << " " << r << "\n";
                ld cval = dp[l][k] + dp[k][r] + dst[l][k] + dst[k][r];
                dp[l][r] = min(dp[l][r], cval);
                if(pt_in_tri(a[l], a[k], a[r], b0)) dpa[l][r] = min(dpa[l][r], cval);
                if(pt_in_tri(a[l], a[k], a[r], b1)) dpb[l][r] = min(dpb[l][r], cval);
            }
            // cout << "DP : " << l << " " << r << " " << dp[l][r] << " " << dpa[l][r] << " " << dpb[l][r] << "\n";
        }
    }
    ld edge_amt = 0;
    for(int i = 0; i < n; i++) edge_amt += dst[i][(i + 1) % n];
    ld ans = 1e18;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; (j + 1) % n != i; j++){
            for(int k = j + 1; k % n != i; k++){
                int ia = i, ib = j % n, ic = k % n;
                if(!legal[ia][ib] || !legal[ib][ic] || !legal[ic][ia]) continue;
                // cout << "FINAL LEGAL : " << ia << " " << ib << " " << ic << "\n";
                {
                    ld cans = 0;
                    cans += dst[ia][ib] + dst[ib][ic] + dst[ic][ia];
                    cans += dpa[ia][ib] + dpb[ib][ic] + dp[ic][ia];
                    ans = min(ans, cans);
                }
                {
                    ld cans = 0;
                    cans += dst[ia][ib] + dst[ib][ic] + dst[ic][ia];
                    cans += dpb[ia][ib] + dpa[ib][ic] + dp[ic][ia];
                    ans = min(ans, cans);
                }
                // cout << "ANS : " << ans << "\n";
            }
        }
    }
    if(ans == 1e18) cout << "IMPOSSIBLE\n";
    else cout << fixed << setprecision(10) << ans - edge_amt << "\n";

    return 0;
}