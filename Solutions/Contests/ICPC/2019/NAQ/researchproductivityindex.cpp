#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ld> p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        p[i] /= 100.0;
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
    vector<vector<ld>> ev(n + 1, vector<ld>(n + 1, 0)); //i = s, j = a, ev to get to i j
    ev[0][0] = 1;
    ld ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            ev[i + 1][j] += ev[i][j] * (1.0 - p[i]);    //not accepted
            ev[i + 1][j + 1] += ev[i][j] * p[i];    //accepted
        }
    }
    for(int i = 1; i <= n; i++){
        ld cur_ans = 0;
        for(int j = 1; j <= i; j++){
            ld s = i;
            ld a = j;
            ld ind = pow(a, a / s);
            cur_ans += ind * ev[s][a];
        }
        ans = max(ans, cur_ans);
    }
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}