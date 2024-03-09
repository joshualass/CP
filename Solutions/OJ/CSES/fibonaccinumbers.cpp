#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    ll n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            for(ll z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
            }
            res[i][j] %= MOD;
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
    
    ll n; cin >> n;

    vector<vector<ll>> mat = {{1,1},{1,0}};
    
    cout << matexp(mat,n)[1][0] << '\n';

    return 0;
}