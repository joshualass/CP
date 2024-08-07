#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll INF = 2e18;

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            res[i][j] = INF;
            for(int z = 0; z < n; z++) {
                res[i][j] = min(res[i][j], a[i][z] + b[z][j]);
            }
        }
    }
    return res;
}
//use notation of [from][to]
vector<vector<ll>> matexp(vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ll>> result(n,vector<ll>(n,INF));
    for(int i = 0; i < n; i++) {
        result[i][i] = 0;
    }
    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
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
    vector<vector<ll>> v(n,vector<ll>(n,INF));
    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        v[a][b] = min(v[a][b],c);
    }
    vector<vector<ll>> res = matexp(v,k);

    cout << (res[0][n-1] == INF ? -1 : res[0][n-1]) << '\n';

    return 0;
}