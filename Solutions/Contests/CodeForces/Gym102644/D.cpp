#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
                res[i][j] %= MOD;
            }
            // res[i][j] %= MOD;
        }
    }
    return res;
}

vector<vector<ll>> matexp(vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ll>> result(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    while(pow) {
        if(pow & 1) {
            result = matmult(mat,result);
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> mat(n,vector<ll>(n));
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        mat[a][b] = 1;
    }

    vector<vector<ll>> res = matexp(mat, k);

    ll ans = 0;
    for(auto x : res) {
        for(auto y : x) {
            ans += y;
            ans %= MOD;
        }
    }   

    cout << ans << '\n';

    return 0;
}